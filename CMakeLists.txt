
cmake_minimum_required(VERSION 3.10)
project(MinecraftClone)

set(CMAKE_CXX_STANDARD 17)

# Include directories
include_directories(external/glfw/include)
include_directories(external/glad/include)

# Add source files
add_executable(MinecraftClone
    src/main.cpp
    external/glad/src/glad.c
)

# Link GLFW statically and OpenGL
target_link_libraries(MinecraftClone
    ${CMAKE_SOURCE_DIR}/external/glfw/lib-mingw-w64/libglfw3.a
    opengl32
)
