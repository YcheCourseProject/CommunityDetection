cmake_minimum_required(VERSION 3.3)
project(Infomap)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")

set(SOURCE_FILES
    Infomap/src/infomap/Edge.h
    Infomap/src/infomap/flowData.h
    Infomap/src/infomap/flowData_traits.h
    Infomap/src/infomap/FlowNetwork.cpp
    Infomap/src/infomap/FlowNetwork.h
    Infomap/src/infomap/InfomapBase.cpp
    Infomap/src/infomap/InfomapBase.h
    Infomap/src/infomap/InfomapContext.cpp
    Infomap/src/infomap/InfomapContext.h
    Infomap/src/infomap/InfomapGreedy.h
    Infomap/src/infomap/InfomapGreedyCommon.h
    Infomap/src/infomap/InfomapGreedySpecialized.h
    Infomap/src/infomap/InfomapGreedyTypeSpecialized.h
    Infomap/src/infomap/MemFlowNetwork.cpp
    Infomap/src/infomap/MemFlowNetwork.h
    Infomap/src/infomap/MemNetwork.cpp
    Infomap/src/infomap/MemNetwork.h
    Infomap/src/infomap/MemoryNetworkAdapter.cpp
    Infomap/src/infomap/MemoryNetworkAdapter.h
    Infomap/src/infomap/MultiplexNetwork.cpp
    Infomap/src/infomap/MultiplexNetwork.h
    Infomap/src/infomap/Network.cpp
    Infomap/src/infomap/Network.h
    Infomap/src/infomap/NetworkAdapter.cpp
    Infomap/src/infomap/NetworkAdapter.h
    Infomap/src/infomap/Node.cpp
    Infomap/src/infomap/Node.h
    Infomap/src/infomap/NodeFactory.h
    Infomap/src/infomap/TreeData.cpp
    Infomap/src/infomap/TreeData.h
    Infomap/src/infomap/treeIterators.h
    Infomap/src/io/BipartiteClusterReader.cpp
    Infomap/src/io/BipartiteClusterReader.h
    Infomap/src/io/ClusterReader.cpp
    Infomap/src/io/ClusterReader.h
    Infomap/src/io/Config.h
    Infomap/src/io/convert.h
    Infomap/src/io/HierarchicalNetwork.cpp
    Infomap/src/io/HierarchicalNetwork.h
    Infomap/src/io/ProgramInterface.cpp
    Infomap/src/io/ProgramInterface.h
    Infomap/src/io/SafeFile.h
    Infomap/src/io/TreeDataWriter.cpp
    Infomap/src/io/TreeDataWriter.h
    Infomap/src/io/version.cpp
    Infomap/src/io/version.h
    Infomap/src/utils/Date.h
    Infomap/src/utils/FileURI.cpp
    Infomap/src/utils/FileURI.h
    Infomap/src/utils/gap_iterator.h
    Infomap/src/utils/infomath.h
    Infomap/src/utils/Logger.cpp
    Infomap/src/utils/Logger.h
    Infomap/src/utils/MersenneTwister.h
    Infomap/src/utils/Stopwatch.h
    Infomap/src/utils/types.h
    Infomap/src/Infomap.cpp
    Infomap/src/Infomap.h
    Infomap/src/Informatter.cpp)

add_executable(Infomap Infomap/src/Infomap.cpp)
add_executable(Example Infomap/examples/cpp/minimal/example.cpp)