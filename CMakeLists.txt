cmake_minimum_required(VERSION 3.3)
project("Iris")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_CXX_STANDARD 17)

add_subdirectory(external/glew)
add_subdirectory(external/glfw)
add_subdirectory(external/glm)

set(SOURCES
    src/main.cpp
    src/Vertex.hpp
    src/backend/VBO.hpp
    src/backend/VBO.cpp
    src/backend/EBO.hpp
    src/backend/EBO.cpp 
    src/backend/VAO.hpp
    src/backend/VAO.cpp
    src/Shader.hpp
    src/Shader.cpp 
    src/Texture.hpp 
    src/Texture.cpp
    src/Mesh.hpp
    src/Mesh.cpp
    src/Core.hpp
    src/Core.cpp 
    src/Renderer.hpp
    src/Renderer.cpp
    src/RenderObject.hpp
    src/RenderObject.cpp
    src/camera/Camera.hpp
    src/camera/OrthographicCamera.hpp
    src/camera/OrthographicCamera.cpp
    src/camera/PerspectiveCamera.hpp
    src/camera/PerspectiveCamera.cpp
)

add_executable(${PROJECT_NAME} ${SOURCES})

target_include_directories(${PROJECT_NAME} PUBLIC src)
target_include_directories(${PROJECT_NAME} PUBLIC shaders)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/glfw/include)
target_link_libraries(${PROJECT_NAME} PUBLIC glfw)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/glew/include)
target_link_libraries(${PROJECT_NAME} PUBLIC libglew_static)

target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/glm)
target_include_directories(${PROJECT_NAME} PUBLIC ${CMAKE_SOURCE_DIR}/external/stb)