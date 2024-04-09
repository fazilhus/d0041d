cmake_minimum_required(VERSION 3.28)
project(main)

set(CMAKE_CXX_STANDARD 20)

add_executable(main
        main.cpp
        src/sort.h
        src/heap.h
        src/hash_table.h
)

add_executable(test 
        test/test.cpp
        test/algo_test.h
        test/sort_test.h
        test/hashtable_test.h
)
