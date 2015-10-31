cmake_minimum_required(VERSION 3.3)
project(src)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    DynamicDistance/CommunityDetection.cpp
    DynamicDistance/CommunityDetection.h
    DynamicDistance/Graph.cpp
    DynamicDistance/Graph.h
    DynamicDistance/Helper.cpp
    DynamicDistance/Helper.h
    DynamicDistance/Main.cpp)

add_executable(src ${SOURCE_FILES})