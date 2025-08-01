#include "InputManager.h"
#include <iostream>

float InputManager::lastX = 0.0f;
float InputManager::lastY = 0.0f;
bool InputManager::firstMouse = true;
InputManager* InputManager::instance = nullptr;

InputManager::InputManager(Camera& cam, float screenWidth, float screenHeight)
    : camera(cam)
{
    lastX = screenWidth / 2.0f;
    lastY = screenHeight / 2.0f;
    firstMouse = true;
    instance = this;
}

void InputManager::ProcessKeyboard(GLFWwindow* window, float deltaTime) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        camera.ProcessKeyboard(RIGHT, deltaTime);
}

void InputManager::MouseCallback(GLFWwindow* window, double xposIn, double yposIn) {
    if (instance)
        instance->HandleMouseMovement(static_cast<float>(xposIn), static_cast<float>(yposIn));
}

void InputManager::ScrollCallback(GLFWwindow* window, double xoffset, double yoffset) {
    if (instance)
        instance->HandleMouseScroll(static_cast<float>(yoffset));
}

void InputManager::HandleMouseMovement(float xpos, float ypos) {
    std::cout << "Mouse moved to: " << xpos << ", " << ypos << std::endl;

    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
    }

    float xoffset = xpos - lastX;
    float yoffset = lastY - ypos; // reversed

    lastX = xpos;
    lastY = ypos;

    camera.ProcessMouseMovement(xoffset, yoffset, true);
}

void InputManager::HandleMouseScroll(float yoffset) {
    camera.ProcessMouseScroll(yoffset);
}
