#ifndef WINDOWMANAGER_H
#define WINDOWMANAGER_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

namespace WindowManager {
    static GLFWwindow* Init(int width, int height, const char* title);
    void framebuffer_size_callback(GLFWwindow* window, int width, int height);
}

#endif
