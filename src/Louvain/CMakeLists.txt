cmake_minimum_required(VERSION 3.3)
project(Community_latest)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    community.cpp
    community.h
    graph.cpp
    graph.h
    graph_binary.cpp
    graph_binary.h
    main_community.cpp
    main_convert.cpp
    main_hierarchy.cpp
    main_random.cpp)

add_executable(Community_latest ${SOURCE_FILES})
add_executable(Convert main_convert.cpp)
add_executable(Community-detection main_community.cpp)
add_executable(Hierarchy main_hierarchy.cpp)