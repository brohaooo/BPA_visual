cmake_minimum_required(VERSION 3.0)

project(BPA_visual)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./)
include_directories(./glad/include)
include_directories(./stb_image)
include_directories(./learnopengl)
include_directories(./glfw-3.3.8/include)

link_directories(./)
link_directories(./depends)

set(HEADERS
        BPA/BallPivotingAlgorithm.h
        rply/rply.h)

set(SOURCES
	main.cpp
        	BPA/BallPivotingAlgorithm.cpp
	rply/rply.c
        )

add_executable(BPA_visual ${HEADERS} ${SOURCES})

target_link_libraries(BPA_visual libglfw3.a)
target_link_libraries(BPA_visual libglad.a)
