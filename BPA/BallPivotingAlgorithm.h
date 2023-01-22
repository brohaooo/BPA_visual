#ifndef BallPivotingAlgorithm
#define BallPivotingAlgorithm


#include <array>
#include <vector>
#include <glm/glm.hpp>

namespace BPA {
	//Triangle is the faces after construction
	struct Triangle : std::array<glm::vec3, 3> {
		glm::vec3 normal() const {
			return glm::normalize(glm::cross((*this)[0] - (*this)[1], (*this)[0] - (*this)[2]));
		}
	};
	//Point is the input type of points, which have both position coordinate and the normal
	struct Point {
		glm::vec3 pos;
		glm::vec3 normal;
	};


	//defined date structures for reconstruction
	struct MeshEdge;
	struct MeshPoint;
	enum class EdgeStatus;
	struct MeshFace;
	struct Grid;
	struct SeedResult;
	struct PivotResult;


	//takes points and radius as input, this function gives faces as output
	auto reconstruct(const std::vector<Point>& points, float radius) -> std::vector<Triangle>;
}

#endif