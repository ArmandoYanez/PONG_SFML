cmake_minimum_required(VERSION 3.28)
project(PONG_SFML)

set(CMAKE_CXX_STANDARD 17)
set(SFML_DIR C:/Users/Armando\.vcpkg-clion/vcpkg/installed/x64-windows/share/sfml)

add_executable(SFML main.cpp)

find_package(SFML 2.5 COMPONENTS graphics system window CONFIG REQUIRED)

target_link_libraries(SFML sfml-graphics sfml-system sfml-window)