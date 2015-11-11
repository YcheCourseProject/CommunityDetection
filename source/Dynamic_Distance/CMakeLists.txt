cmake_minimum_required(VERSION 3.3)
project(src)
set(CMAKE_BUILD_TYPE Realease)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "/home/cheyulin/ClionProjects/Community-Detection/build")
set(SOURCE_FILES
    DynamicDistance/ClusteringEvaluation.cpp
    DynamicDistance/ClusteringEvaluation.h
    DynamicDistance/CommunityDetection.cpp
    DynamicDistance/CommunityDetection.h
    DynamicDistance/Graph.cpp
    DynamicDistance/Graph.h
    DynamicDistance/Helper.cpp
    DynamicDistance/Helper.h
    DynamicDistance/Main.cpp
)

add_executable(attractorImproveEI ${SOURCE_FILES})