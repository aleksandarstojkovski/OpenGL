cmake_minimum_required(VERSION 3.10)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME House_OpenGL3)
set(SOURCE_FILES main.cpp lib/RgbImage.cpp)
set(CMAKE_CXX_FLAGS "-fpermissive -Wwrite-strings -std=c++0x")

configure_file(images/door.bmp images/door.bmp COPYONLY)
configure_file(images/roof.bmp images/roof.bmp COPYONLY)
configure_file(images/wall.bmp images/wall.bmp COPYONLY)
configure_file(images/flag.bmp images/flag.bmp COPYONLY)
configure_file(../README.txt README.txt COPYONLY)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

find_package(OpenGL REQUIRED)
find_package(GLUT REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${GLUT_INCLUDE_DIRS})

target_link_libraries(${PROJECT_NAME} ${OPENGL_LIBRARIES} ${GLUT_LIBRARY})