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
    DynamicDistance/Main.cpp )

add_executable(src ${SOURCE_FILES})
add_executable(InputMetis IO/MetisInputPreProcess.cpp)
add_executable(InfomapOutputProcess IO/InfomapOutputProcess.cpp)
add_executable(Test Experiment/TestMain.cpp Experiment/TestMain.h )
add_executable(Test2 Experiment/Test2.cpp)