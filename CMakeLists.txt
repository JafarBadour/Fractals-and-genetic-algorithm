cmake_minimum_required(VERSION 3.13)

project(Jafar)

find_package(OpenCV REQUIRED) # after project()
set(CMAKE_CXX_STANDARD 14)



add_executable(Jafar main.cpp)

target_link_libraries( Jafar ${OpenCV_LIBS} )

include_directories(${OpenCV_INCLUDE_DIRS})

