cmake_minimum_required(VERSION 3.16)
project(amp-sim)

set(CMAKE_CXX_STANDARD 17)

find_package(PkgConfig REQUIRED)
pkg_check_modules(RTAUDIO REQUIRED rtaudio)
find_package(SFML 3 COMPONENTS Graphics Window System REQUIRED)

add_executable(amp-sim
    src/main.cpp
    src/ui/UI.cpp
    src/ui/Slider.cpp
)

target_include_directories(amp-sim PRIVATE
    src/
    /opt/homebrew/Cellar/rtaudio/6.0.1/include/rtaudio
    ${RTAUDIO_INCLUDE_DIRS}
)

target_link_directories(amp-sim PRIVATE /opt/homebrew/lib)

target_link_libraries(amp-sim PRIVATE
    ${RTAUDIO_LIBRARIES}
    SFML::Graphics
    SFML::Window
    SFML::System
)