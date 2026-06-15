cmake_minimum_required(VERSION 3.16)
project(amp-sim)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(RTAUDIO REQUIRED rtaudio)

add_executable(amp-sim src/main.cpp)
target_include_directories(amp-sim PRIVATE ${RTAUDIO_INCLUDE_DIRS})
target_link_libraries(amp-sim PRIVATE ${RTAUDIO_LIBRARIES})
target_link_directories(amp-sim PRIVATE /opt/homebrew/lib)