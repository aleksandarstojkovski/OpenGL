cmake_minimum_required(VERSION 3.10)
project(OpenGL)

set(CMAKE_CXX_STANDARD 14)
set(PROJECT_NAME Door_OpenGL3)
set(SOURCE_FILES main.cpp lib/RgbImage.cpp shaders_loader.cpp shaders_loader.h)
set(CMAKE_CXX_FLAGS "-fpermissive -Wwrite-strings -std=c++0x")

configure_file(images/door.bmp images/door.bmp COPYONLY)
configure_file(images/roof.bmp images/roof.bmp COPYONLY)
configure_file(images/wall.bmp images/wall.bmp COPYONLY)
configure_file(images/flag.bmp images/flag.bmp COPYONLY)
configure_file(../README.txt README.txt COPYONLY)

add_executable(${PROJECT_NAME} ${SOURCE_FILES})

if(APPLE)
    message(INFO ": PLATFORM APPLE")
    include_directories("/usr/local/include")

    # FIND OPENGL
    #########################################################
    find_package(OpenGL REQUIRED)
    include_directories(${OpenGL_INCLUDE_DIRS})
    link_directories(${OpenGL_LIBRARY_DIRS})
    add_definitions(${OpenGL_DEFINITIONS})
    if(NOT OPENGL_FOUND)
        message(ERROR " OPENGL not found!")
    endif(NOT OPENGL_FOUND)

    # FIND GLUT
    # NOTA: in realtà si tratta della libreria FreeGLUT
    #########################################################
    find_package(GLUT REQUIRED)
    include_directories(${GLUT_INCLUDE_DIRS})
    link_directories(${GLUT_LIBRARY_DIRS})
    add_definitions(${GLUT_DEFINITIONS})
    if(NOT GLUT_FOUND)
        message(ERROR " GLUT not found!")
    endif(NOT GLUT_FOUND)



    # GLEW
    #########################################################
    find_package(GLEW)
    include_directories(${GLEW_INCLUDE_DIR})
    link_libraries(${GLEW_LIBRARIES})
    include_directories("/usr/local/include")
    link_libraries("/usr/local/lib/libGLEW.a")



    # GLFW.
    #########################################################
    find_package(GLFW3 REQUIRED)
    include_directories(${GLFW3_INCLUDE_DIR})

    # Set necessary libs.
    set(REQUIRED_LIBS
            ${GLUT_LIBRARY}
            ${GLFW3_LIBRARIES}
            ${GLEW_LIBRARIES}
            ${OPENGL_LIBRARY}
            )
else()

    message(INFO ": PLATFORM WINDOWS")

    set(CMAKE_PREFIX_PATH "C:/SUPSI/opengl/freeglut")

    include_directories("C:/SUPSI/opengl/freeglut/include")
    link_directories("C:/SUPSI/opengl/freeglut/lib/x64")

    include_directories("C:/SUPSI/opengl/glew-2.1.0/include")
    link_directories("C:/SUPSI/opengl/glew-2.1.0/lib/release/x64")

    include_directories("C:/SUPSI/opengl/glm-0.9.9.8/glm")

    set(OPENGL_LIBRARY -lopengl32)
    set(GLUT_LIBRARY -lfreeGLUT -lglu32)
    set(GLEW_LIBRARIES -lglew32)

endif()

# Set necessary libs.
set(REQUIRED_LIBS
        ${GLUT_LIBRARY}
        ${GLFW3_LIBRARIES}
        ${GLEW_LIBRARIES}
        ${OPENGL_LIBRARY}
        )

configure_file(shaders/shader.frag shaders/shader.frag COPYONLY)
configure_file(shaders/shader.vert shaders/shader.vert COPYONLY)

configure_file(images/door.bmp images/door.bmp COPYONLY)
configure_file(../README.txt README.txt COPYONLY)


target_link_libraries(${PROJECT_NAME} ${REQUIRED_LIBS})
