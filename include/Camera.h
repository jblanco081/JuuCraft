#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

enum Camera_Movement {
    FORWARD,
    BACKWARD,
    LEFT,
    RIGHT
};

class Camera {
public:
    glm::vec3 Position;
    glm::vec3 Front;
    glm::vec3 Up;
    glm::vec3 Right;
    glm::vec3 WorldUp;

    float Yaw;
    float Pitch;

    float MovementSpeed;
    float MouseSensitivity;
    float Zoom;

Camera(glm::vec3 position = glm::vec3(0.0f, 0.0f, 3.0f),
       glm::vec3 up = glm::vec3(0.0f, 1.0f, 0.0f),
       float yaw = -90.0f,
       float pitch = 0.0f);
       
    glm::mat4 GetViewMatrix();

    void ProcessKeyboard(Camera_Movement direction, float deltaTime);
    void ProcessMouseMovement(float xOffset, float yOffset, bool constrainPitch = true);
    void ProcessMouseScroll(float yOffset);

private:
    void updateCameraVectors();
};

#endif
