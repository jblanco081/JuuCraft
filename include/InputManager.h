// InputManager.h
#pragma once
#include <GLFW/glfw3.h>
#include "Camera.h"

class InputManager {
public:
    InputManager(Camera& cam, float screenWidth, float screenHeight);

    void ProcessKeyboard(GLFWwindow* window, float deltaTime);

    static void MouseCallback(GLFWwindow* window, double xpos, double ypos);
    static void ScrollCallback(GLFWwindow* window, double xoffset, double yoffset);

private:
    Camera& camera;

    static float lastX;
    static float lastY;
    static bool firstMouse;

    // Since callbacks must be static, store a static pointer to the instance
    static InputManager* instance;

    void HandleMouseMovement(float xpos, float ypos);
    void HandleMouseScroll(float yoffset);
};
