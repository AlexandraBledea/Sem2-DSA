cmake_minimum_required(VERSION 3.17)
project(MultiMap_PW4)

set(CMAKE_CXX_STANDARD 14)

include_directories(ExtendedTest)
include_directories(MultiMap)
include_directories(MultiMapIterator)
include_directories(ShortTest)

add_executable(MultiMap_PW4
        ExtendedTest/ExtendedTest.h
        ExtendedTest/ExtendedTest.cpp
        ShortTest/ShortTest.h
        ShortTest/ShortTest.cpp
        MultiMapIterator/MultiMapIterator.h
        MultiMapIterator/MultiMapIterator.cpp
        MultiMap/MultiMap.h
        MultiMap/MultiMap.cpp
        App.cpp)