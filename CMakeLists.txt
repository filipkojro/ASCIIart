cmake_minimum_required(VERSION 3.27.7)
project(ASCIIart)

include_directories(./raylib/include/)
link_directories(./raylib/lib/)

set(CMAKE_CXX_STANDARD 14)

add_executable(ASCIIart main.cpp)

target_link_libraries(ASCIIart raylib)
