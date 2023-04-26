cmake_minimum_required(VERSION 3.25)
project(JakDojade)

set(CMAKE_CXX_STANDARD 17)

add_executable(JakDojade main.cpp tstring/tString.cpp Neighbour.cpp City.cpp City.h JakDojade.cpp JakDojade.h tPriorityQueue.cpp)
add_executable(Struct_Test main.cpp tstring/tString.cpp)
add_executable(City_Test main.cpp tstring/tString.cpp Neighbour.cpp City.cpp City.h)
include_directories(tstring)
include_directories(tvector)
include_directories(tpriority_queue)