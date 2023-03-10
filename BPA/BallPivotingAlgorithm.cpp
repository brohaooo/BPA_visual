#include "BallPivotingAlgorithm.h"

#include <algorithm>
#include <deque>
#include <optional>
#include <string>
#include <iostream>
#include <sstream>
#include <numeric>
#include <tuple>
#include <math.h>

#include "glm/gtx/io.hpp"

using namespace glm;

namespace BPA {
	
	//points in mesh structure, which have 'used' indicating whether this point has been used for an iteration of ball,
	//and a set of edges this point has
	struct MeshPoint {
		vec3 pos;
		vec3 normal;
		bool used = false;
		std::vector<MeshEdge*> edges;
	};
	//each edge has three status: active(new added edges, good to pivot on), 
	//inner(edges has already been pivoted), boundary(tried to pivot, but no target points are found)
	enum class EdgeStatus {
		active,
		inner,
		boundary
	};
	//edges in mesh structure, which have two points and an opposite point(the point reached after pivoting), the center
	//of such pivoting, the next and previous edges, and  its status
	struct MeshEdge {
		MeshPoint* a;
		MeshPoint* b;
		MeshPoint* opposite;
		vec3 center;
		MeshEdge* prev;
		MeshEdge* next;
		EdgeStatus status = EdgeStatus::active;
	};
	//faces in mesh structure, contains thress mesh points
	struct MeshFace : std::array<MeshPoint*, 3>{
		auto normal() const {
			return normalize(cross((*this)[0]->pos - (*this)[1]->pos, (*this)[0]->pos - (*this)[2]->pos));
		}
	};
	//the first seed result (face and the ball's center)
	struct SeedResult {
		MeshFace f;
		vec3 ballCenter;
	};
	//the pivot result after the BPA, which is the target point and the corresponding ball's center
	struct PivotResult {
		MeshPoint* p;
		vec3 center;
	};

	//a cube in the total space, stores all the points inside it
	using Cell = std::vector<MeshPoint>;

	//the sum of all cubes, which is the entire input space covering all the points
	struct Grid {
		Grid(const std::vector<Point>& points, float radius)
			: cellSize(radius * 2) {
			lower = points.front().pos;
			upper = points.front().pos;

			for (const auto& p : points) {
				for (auto i = 0; i < 3; i++) {
					lower[i] = std::min(lower[i], p.pos[i]);
					upper[i] = std::max(upper[i], p.pos[i]);
				}
			}

			dims = max(ivec3{ceil((upper - lower) / cellSize)}, ivec3{1});

			cells.resize(dims.x * dims.y * dims.z);
			for (const auto& p : points)
				cell(cellIndex(p.pos)).push_back({p.pos, p.normal});
		}

		auto cellIndex(vec3 point) -> ivec3 {
			const auto index = ivec3{(point - lower) / cellSize};
			return clamp(index, ivec3{}, dims - 1);
		}

		auto cell(ivec3 index) -> Cell& {
			return cells[index.z * dims.x * dims.y + index.y * dims.x + index.x];
		}

		auto sphericalNeighborhood(vec3 point, std::initializer_list<vec3> ignore) -> std::vector<MeshPoint*> {
			std::vector<MeshPoint*> result;
			const auto centerIndex = cellIndex(point);
			result.reserve(cell(centerIndex).size() * 27); // just an estimate
			for (auto xOff : {-1, 0, 1}) {
				for (auto yOff : {-1, 0, 1}) {
					for (auto zOff : {-1, 0, 1}) {
						const auto index = centerIndex + ivec3{xOff, yOff, zOff};
						if (index.x < 0 || index.x >= dims.x) continue;
						if (index.y < 0 || index.y >= dims.y) continue;
						if (index.z < 0 || index.z >= dims.z) continue;
						for (auto& p : cell(index))
							if (length2(p.pos - point) < cellSize * cellSize && std::find(begin(ignore), end(ignore), p.pos) == end(ignore))
								result.push_back(&p);
					}
				}
			}
			return result;
		}

		vec3 lower;
		vec3 upper;
		float cellSize;
		ivec3 dims;
		std::vector<Cell> cells;
	};
	//compute the ball's center via it's connecting face and radius, return its center's position
	auto computeBallCenter(MeshFace f, float radius) -> std::optional<vec3> {
		const vec3 ac = f[2]->pos - f[0]->pos;
		const vec3 ab = f[1]->pos - f[0]->pos;
		const vec3 abXac = cross(ab, ac);
		const vec3 toCircumCircleCenter = (cross(abXac, ab) * dot(ac, ac) + cross(ac, abXac) * dot(ab, ab)) / (2 * dot(abXac, abXac));
		const vec3 circumCircleCenter = f[0]->pos + toCircumCircleCenter;

		const auto heightSquared = radius * radius - dot(toCircumCircleCenter, toCircumCircleCenter);
		if (heightSquared < 0)
			return {};
		auto ballCenter = circumCircleCenter + f.normal() * std::sqrt(heightSquared);
		return ballCenter;
	}
	//check whether the current ball doesn't include any points inside it, if so such pivoting way is illegal
	auto ballIsEmpty(vec3 ballCenter, const std::vector<MeshPoint*>& points, float radius) -> bool {
		return !std::any_of(begin(points), end(points), [&](MeshPoint* p) {
			return length2(p->pos - ballCenter) < radius * radius - 1e-4f; // TODO epsilon
		});
	}

	//returns the first seed result (face and the ball's center), if no trangle is found, it returns null
	auto findSeedTriangle(Grid& grid, float radius) -> std::optional<SeedResult> {
		for (auto& cell : grid.cells) {
			const auto avgNormal = normalize(std::accumulate(begin(cell), end(cell), vec3{}, [](vec3 acc, const MeshPoint& p) {
				return acc + p.normal;
			}));
			for (auto& p1 : cell) {
				auto neighborhood = grid.sphericalNeighborhood(p1.pos, {p1.pos});
				std::sort(begin(neighborhood), end(neighborhood), [&](MeshPoint* a, MeshPoint* b) {
					return length(a->pos - p1.pos) < length(b->pos - p1.pos);
				});

				for (auto& p2 : neighborhood) {
					for (auto& p3 : neighborhood) {
						if (p2 == p3) continue;
						MeshFace f{{&p1, p2, p3}};
						if (dot(f.normal(), avgNormal) < 0) // only accept triangles which's normal points into the same half-space as the average normal of this cell's points
							continue;
						const auto ballCenter = computeBallCenter(f, radius);
						if (ballCenter && ballIsEmpty(ballCenter.value(), neighborhood, radius)) {
							p1.used = true;
							p2->used = true;
							p3->used = true;
							return SeedResult{f, ballCenter.value()};
						}
					}
				}
			}
		}
		return {};
	}
	//from frontiers get one front edge, it will clean this edge in next iteration because it is not front edge any more
	auto getActiveEdge(std::vector<MeshEdge*>& front) -> std::optional<MeshEdge*> {
		while (!front.empty()) {
			auto* e = front.back();
			if (e->status == EdgeStatus::active)
				return e;
			front.pop_back(); // cleanup non-active edges from front
		}
		return {};
	}

	
	//pivoting at one edge, return the target point and the corresponding ball's center. If no point is found, it returns empty 
	auto ballPivot(const MeshEdge* e, Grid& grid, float radius) -> std::optional<PivotResult> {
		const auto m = (e->a->pos + e->b->pos) / 2.0f;
		const auto oldCenterVec = normalize(e->center - m);
		auto neighborhood = grid.sphericalNeighborhood(m, {e->a->pos, e->b->pos, e->opposite->pos});

		static auto counter = 0;
		counter++;

		auto smallestAngle = std::numeric_limits<float>::max();
		MeshPoint* pointWithSmallestAngle = nullptr;
		vec3 centerOfSmallest{};
		std::stringstream ss;
		auto i = 0;
		int smallestNumber = 0;
		for (const auto& p : neighborhood) {
			i++;
			auto newFaceNormal = Triangle{e->b->pos, e->a->pos, p->pos}.normal();

			// this check is not in the paper: all points' normals must point into the same half-space
			if (dot(newFaceNormal, p->normal) < 0)
				continue;

			const auto c = computeBallCenter(MeshFace{{e->b, e->a, p}}, radius);
			if (!c) {
				continue;
			}

			// this check is not in the paper: the ball center must always be above the triangle
			const auto newCenterVec = normalize(c.value() - m);
			const auto newCenterFaceDot = dot(newCenterVec, newFaceNormal);
			if (newCenterFaceDot < 0) {
				continue;
			}

			// this check is not in the paper: points to which we already have an inner edge are not considered
			for (const auto* ee : p->edges) {
				const auto* otherPoint = ee->a == p ? ee->b : ee->a;
				if (ee->status == EdgeStatus::inner && (otherPoint == e->a || otherPoint == e->b)) {
					goto nextneighbor;
				}
			}

			{
				auto angle = std::acos(std::clamp(dot(oldCenterVec, newCenterVec), -1.0f, 1.0f));
				if (dot(cross(newCenterVec, oldCenterVec), e->a->pos - e->b->pos) < 0)
					angle += M_PI;
				if (angle < smallestAngle) {
					smallestAngle = angle;
					pointWithSmallestAngle = p;
					centerOfSmallest = c.value();
					smallestNumber = i;
				}
			}
		nextneighbor:;
		}

		if (smallestAngle != std::numeric_limits<float>::max()) {
			if (ballIsEmpty(centerOfSmallest, neighborhood, radius)) {
				return PivotResult{pointWithSmallestAngle, centerOfSmallest};
			}
		}

		return {};
	}

	auto notUsed(const MeshPoint* p) -> bool {
		return !p->used;
	}

	auto onFront(const MeshPoint* p) -> bool {
		return std::any_of(begin(p->edges), end(p->edges), [&](const MeshEdge* e) {
			return e->status == EdgeStatus::active;
		});
	}

	void remove(MeshEdge* edge) {
		// just mark the edge as inner. The edge will be removed later in getActiveEdge()
		edge->status = EdgeStatus::inner;
	}

	void outputTriangle(MeshFace f, std::vector<Triangle>& triangles) {
		triangles.push_back({f[0]->pos, f[1]->pos, f[2]->pos});
	}

	auto join(MeshEdge* e_ij, MeshPoint* o_k, vec3 o_k_ballCenter, std::vector<MeshEdge*>& front, std::deque<MeshEdge>& edges) -> std::tuple<MeshEdge*, MeshEdge*> {
		auto& e_ik = edges.emplace_back(MeshEdge{e_ij->a, o_k, e_ij->b, o_k_ballCenter});
		auto& e_kj = edges.emplace_back(MeshEdge{o_k, e_ij->b, e_ij->a, o_k_ballCenter});

		e_ik.next = &e_kj;
		e_ik.prev = e_ij->prev;
		e_ij->prev->next = &e_ik;
		e_ij->a->edges.push_back(&e_ik);

		e_kj.prev = &e_ik;
		e_kj.next = e_ij->next;
		e_ij->next->prev = &e_kj;
		e_ij->b->edges.push_back(&e_kj);

		o_k->used = true;
		o_k->edges.push_back(&e_ik);
		o_k->edges.push_back(&e_kj);

		front.push_back(&e_ik);
		front.push_back(&e_kj);
		remove(e_ij);

		return {&e_ik, &e_kj};
	}
	//if two edges are actually the same, this function will merge them together
	void glue(MeshEdge* a, MeshEdge* b, std::vector<MeshEdge*>& front) {

		// case 1
		if (a->next == b && a->prev == b && b->next == a && b->prev == a) {
			remove(a);
			remove(b);
			return;
		}
		// case 2
		if (a->next == b && b->prev == a) {
			a->prev->next = b->next;
			b->next->prev = a->prev;
			remove(a);
			remove(b);
			return;
		}
		if (a->prev == b && b->next == a) {
			a->next->prev = b->prev;
			b->prev->next = a->next;
			remove(a);
			remove(b);
			return;
		}
		// case 3/4
		a->prev->next = b->next;
		b->next->prev = a->prev;
		a->next->prev = b->prev;
		b->prev->next = a->next;
		remove(a);
		remove(b);
	}

	auto findReverseEdgeOnFront(MeshEdge* edge) -> MeshEdge* {
		for (auto& e : edge->a->edges)
			if (e->a == edge->b)
				return e;
		return nullptr;
	}
	
	//reconstructing the entire point cloud, gives faces as output
	auto reconstruct(const std::vector<Point>& points, float radius) -> std::vector<Triangle> {
		//construct grid spaces
		Grid grid(points, radius);
		//get the initial starting face
		const auto seedResult = findSeedTriangle(grid, radius);
		//if no face is found, the algorthm terminates
		if (!seedResult) {
			std::cerr << "No seed triangle found, perhaps the radius is too small!!!\n";
			return {};
		}
		//generate face set and edge set
		std::vector<Triangle> triangles;
		std::deque<MeshEdge> edges;
		//seed is the three points of the initial face
		//set up this face and its points and edges
		auto [seed, ballCenter] = seedResult.value();
		outputTriangle(seed, triangles);
		auto& e0 = edges.emplace_back(MeshEdge{seed[0], seed[1], seed[2], ballCenter});
		auto& e1 = edges.emplace_back(MeshEdge{seed[1], seed[2], seed[0], ballCenter});
		auto& e2 = edges.emplace_back(MeshEdge{seed[2], seed[0], seed[1], ballCenter});
		e0.prev = e1.next = &e2;
		e0.next = e2.prev = &e1;
		e1.prev = e2.next = &e0;
		seed[0]->edges = { &e0, &e2 };
		seed[1]->edges = { &e0, &e1 };
		seed[2]->edges = { &e1, &e2 };
		//add three intial edges as three members of the frontier
		std::vector<MeshEdge*> front{&e0, &e1, &e2};
		//BPA iterations:
		while (auto e_ij = getActiveEdge(front)) {
			//get the target point via BPA
			const auto o_k = ballPivot(e_ij.value(), grid, radius);
			//such point must (1.exist 2.not used or has at least one of its edges on front, indicating that edge can be used in pivoting)
			if (o_k && (notUsed(o_k->p) || onFront(o_k->p))) {
				//add such face in the result 
				outputTriangle({{e_ij.value()->a, o_k->p, e_ij.value()->b}}, triangles);
				//merge extra edges if needed
				auto [e_ik, e_kj] = join(e_ij.value(), o_k->p, o_k->center, front, edges);
				if (auto* e_ki = findReverseEdgeOnFront(e_ik)) glue(e_ik, e_ki, front);
				if (auto* e_jk = findReverseEdgeOnFront(e_kj)) glue(e_kj, e_jk, front);
			} else {
				e_ij.value()->status = EdgeStatus::boundary;
			}
		}
		return triangles;
	}
}