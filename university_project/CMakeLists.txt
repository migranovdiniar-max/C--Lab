cmake_minimum_required(VERSION 3.10)
project(UniversityManagement)

set(CMAKE_CXX_STANDARD 11)

include_directories(headers)

add_executable(university
    sources/main.cpp
    sources/Student.cpp
    sources/Teacher.cpp
    sources/Administrative.cpp
    sources/Keeper.cpp
)