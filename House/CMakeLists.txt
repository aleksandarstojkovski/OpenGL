cmake_minimum_required(VERSION 3.15)
project(s4_es1 C)

set(CMAKE_C_STANDARD 99)
set(PROJECT_NAME House)
set(SOURCE_FILES main.c)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})