cmake_minimum_required(VERSION 3.23)
project(tikiNES LANGUAGES C CXX)

add_executable(tikiNES src/main.cpp)

set_property(TARGET tikiNES PROPERTY CXX_STANDARD 17)