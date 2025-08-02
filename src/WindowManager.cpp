#include "WindowManager.h"
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

namespace WindowManager {

    GLFWwindow* WindowManager::Init(int width, int height, const char* title) {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_CORE_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(width, height, title, NULL, NULL);
    if (!window) {
        std::cerr << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return nullptr;
    }

    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize GLAD" << std::endl;
        return nullptr;
    }

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

     glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }

    glEnable(GL_DEPTH_TEST);

    return window;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

}
