cmake_minimum_required(VERSION 3.17)
project(ADTMatrix_PW5)

set(CMAKE_CXX_STANDARD 14)

include_directories(ExtendedTest)
include_directories(Matrix)
include_directories(ShortTest)

add_executable(ADTMatrix_PW5
        ExtendedTest/ExtendedTest.cpp
        ExtendedTest/ExtendedTest.h
        Matrix/Matrix.cpp
        Matrix/Matrix.h
        ShortTest/ShortTest.cpp
        ShortTest/ShortTest.h
        App.cpp)
