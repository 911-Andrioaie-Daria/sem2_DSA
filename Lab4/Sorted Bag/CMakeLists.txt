cmake_minimum_required(VERSION 3.19)
project(Sorted_Bag)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Sorted_Bag
        App.cpp
        ExtendedTest.cpp
        ExtendedTest.h
        ShortTest.cpp
        ShortTest.h
        SortedBag.cpp
        SortedBag.h
        SortedBagIterator.cpp
        SortedBagIterator.h)
