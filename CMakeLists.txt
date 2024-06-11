cmake_minimum_required(VERSION 3.26.0)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(gatsProject VERSION 0.1.0 LANGUAGES C CXX)
include_directories(/opt/homebrew/include)
add_executable(hormigasProject main.cpp mapa.cpp hormiga.cpp colonia.cpp)
