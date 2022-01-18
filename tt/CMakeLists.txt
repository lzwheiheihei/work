cmake_minimum_required(VERSION 3.20)
project(tt)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g -O3 -fprofile-arcs -ftest-coverage")
add_executable(tt
        dictMatch.cpp trie.h)
