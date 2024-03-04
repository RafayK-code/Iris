cmake_minimum_required(VERSION 3.3)
project("Iris")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glew)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

set(SOURCES
    src/main.cpp 
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} src)
target_include_directories(${PROJECT_NAME} shaders)

target_include_directories(${PROJECT_NAME} PUBLIC glfw/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

target_include_directories(${PROJECT_NAME} PUBLIC glew/include)
target_link_libraries(${PROJECT_NAME} PUBLIC libglew_shared)