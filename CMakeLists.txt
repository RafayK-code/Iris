cmake_minimum_required(VERSION 3.3)
project("Iris")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glew)
add_subdirectory(external/glfw)

set(SOURCES
    src/main.cpp 
)

add_executable(${PROJECT_NAME} ${SOURCES})