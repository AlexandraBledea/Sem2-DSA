cmake_minimum_required(VERSION 3.17)
project(PracticalWork1)

set(CMAKE_CXX_STANDARD 14)

add_executable(PracticalWork1
        ExtendedTest/ExtendedTest.h
        ExtendedTest/ExtendedTest.cpp
        ShortTest/ShortTest.h
        ShortTest/ShortTest.cpp
        SortedBag/SortedBag.cpp
        SortedBag/SortedBag.h
        SortedBagIterator/SortedBagIterator.cpp
        SortedBagIterator/SortedBagIterator.h
        App.cpp)