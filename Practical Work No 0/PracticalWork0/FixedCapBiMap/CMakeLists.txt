cmake_minimum_required(VERSION 3.17)
project(FixedCapBiMap)
set(CMAKE_C_STANDARD 11)
include_directories(ExtendedTest)
include_directories(FixedCapBiMap)
include_directories(FixedCapBiMapIterator)
include_directories(ShortTest)

add_executable(FixedCapBiMap
        ExtendedTest/ExtendedTest.cpp
        ExtendedTest/ExtendedTest.h
        FixedCapBiMap/FixedCapBiMap.cpp
        FixedCapBiMap/FixedCapBiMap.h
        FixedCapBiMapIterator/FixedCapBiMapIterator.cpp
        FixedCapBiMapIterator/FixedCapBiMapIterator.h
        ShortTest/ShortTest.cpp
        ShortTest/ShortTest.h
        App.cpp)
