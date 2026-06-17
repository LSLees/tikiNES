cmake_minimum_required(VERSION 3.23)

project(tikiNES LANGUAGES C CXX)

include_directories(
  src
  contrib/cl-windows/include
)

link_directories(
  contrib/cl-windows/lib
)

add_library(coreNES
  src/cpu.cpp
  src/mem.cpp
  src/nes.cpp
  src/ppu.cpp

  include/common.h
  include/cpu.h
  include/mem.h
  include/nes.h
  include/ppu.h
)

target_link_libraries(coreNES SDL3)

add_executable(tikiNES 
  src/main.cpp
)

target_link_libraries(tikiNES coreNES)

set_property(TARGET tikiNES PROPERTY CXX_STANDARD 17)