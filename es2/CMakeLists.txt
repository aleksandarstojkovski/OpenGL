cmake_minimum_required(VERSION 3.15)
project(es2 C)

set(CMAKE_C_STANDARD 99)

add_executable(es2 main.c)

target_link_libraries(es2 -lfreeGLUT -lglew32 -lopengl32 -lglu32)