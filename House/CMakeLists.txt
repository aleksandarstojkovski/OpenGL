cmake_minimum_required(VERSION 3.15)
project(s4_es1 C)

set(CMAKE_C_STANDARD 99)

add_executable(House main.c)

target_link_libraries(House -lfreeGLUT -lglew32 -lopengl32 -lglu32)