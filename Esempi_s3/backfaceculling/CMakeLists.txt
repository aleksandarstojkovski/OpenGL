set(
        CMAKE_RUNTIME_OUTPUT_DIRECTORY
        ${CMAKE_HOME_DIRECTORY}/serie3/backfaceculling
)

add_executable(backfaceculling main.cpp imageloader.cpp imageloader.h)

target_link_libraries(backfaceculling ${REQUIRED_LIBS} )
