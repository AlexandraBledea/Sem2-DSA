cmake_minimum_required(VERSION 3.17)
project(SortedMap_PW2)

set(CMAKE_CXX_STANDARD 14)

include_directories(ExtendedTest)
include_directories(ShortTest)
include_directories(SMIterator)
include_directories(SortedMap)

add_executable(SortedMap_PW2
        ExtendedTest/ExtendedTest.cpp
        ExtendedTest/ExtendedTest.h
        ShortTest/ShortTest.cpp
        ShortTest/ShortTest.h
        SMIterator/SMIterator.cpp
        SMIterator/SMIterator.h
        SortedMap/SortedMap.cpp
        SortedMap/SortedMap.h
        App.cpp)
