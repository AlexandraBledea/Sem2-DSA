cmake_minimum_required(VERSION 3.17)
project(SortedMultiMap_PW3)

set(CMAKE_CXX_STANDARD 14)
include_directories(ExtendedTest)
include_directories(ShortTest)
include_directories(SMMIterator)
include_directories(SortedMultiMap)

add_executable(SortedMultiMap_PW3
        ExtendedTest/ExtendedTest.cpp
        ExtendedTest/ExtendedTest.h
        ShortTest/ShortTest.cpp
        ShortTest/ShortTest.h
        SMMIterator/SMMIterator.cpp
        SMMIterator/SMMIterator.h
        SortedMultiMap/SortedMultiMap.cpp
        SortedMultiMap/SortedMultiMap.h
        App.cpp)