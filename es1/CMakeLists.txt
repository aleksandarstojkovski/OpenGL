cmake_minimum_required(VERSION 3.15)
project(es1 C)

set(CMAKE_C_STANDARD 99)

add_executable(es1 main.c)

target_link_libraries(es1 -lfreeGLUT -lglew32 -lopengl32 -lglu32)