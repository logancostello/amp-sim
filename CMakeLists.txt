cmake_minimum_required(VERSION 3.16)
project(amp-sim)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)

add_executable(amp-sim src/main.cpp)