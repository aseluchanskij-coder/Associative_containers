cmake_minimum_required(VERSION 3.10)

project(TekstoAnalize)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(programa project/main.cpp project/utils.cpp)
add_executable(papildoma project/papildoma.cpp project/utils.cpp)