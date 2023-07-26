cmake_minimum_required(VERSION 3.20                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                )
project(aed2122_trabalho2)

set(CMAKE_CXX_STANDARD 20)


include_directories(Classes)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR})


set(BUILD_1 main)
set(SOURCE_FILES_1
        Classes/AuxiliaryFunctions.cpp
        Classes/AuxiliaryFunctions.h
        Classes/menu.cpp
        Classes/menu.h
        main.cpp
        Classes/Menu.cpp
        Classes/Menu.h
        Classes/disjointSets.h
        Classes/graph.h
        Classes/graph.cpp
        Classes/minHeap.h Classes/Stcp.cpp Classes/Stcp.h Classes/LineGraph.cpp Classes/LineGraph.h)
add_executable(${BUILD_1} ${SOURCE_FILES_1})

set(BUILD_2 tests)
set(SOURCE_FILES_2 "Tests and Examples/code_testing.cpp"
        Classes/AuxiliaryFunctions.cpp
        Classes/AuxiliaryFunctions.h
        Classes/disjointSets.h
        Classes/minHeap.h
        Classes/graph.h
        Classes/graph.cpp
        Classes/menu.cpp
        Classes/menu.h
        Classes/Menu.cpp Classes/Menu.h Classes/Stcp.cpp Classes/Stcp.h Classes/LineGraph.cpp Classes/LineGraph.h)
add_executable(${BUILD_2} ${SOURCE_FILES_2})

