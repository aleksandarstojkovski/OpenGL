cmake_minimum_required(VERSION 3.10)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME untitled)
set(SOURCE_FILES main.cpp lib/RgbImage.cpp)
set(CMAKE_CXX_FLAGS "-fpermissive -Wwrite-strings -std=c++0x")

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})