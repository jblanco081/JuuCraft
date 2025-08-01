#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <Shader.h>
#include <Camera.h>
#include <stb_image.h>
#include <vector>
#include <string>
#include <glm/gtc/type_ptr.hpp>
#include "Chunk.h"
#include <InputManager.h>
#include "TextureManager.h"
#include "WindowManager.h"

// settings
const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

// camera
Camera camera;
InputManager inputManager(camera, SCR_WIDTH, SCR_HEIGHT);

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "Learn OpenGL", NULL, NULL);

    if (window == NULL) {

        std::cout << "Failed to create GLFW window" << std::endl;

        glfwTerminate();

        return -1;
    }

    glfwMakeContextCurrent(window);

    glfwSetCursorPosCallback(window, InputManager::MouseCallback);
    glfwSetScrollCallback(window, InputManager::ScrollCallback);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {

        std::cout << "Failed to initialize GLAD" << std::endl;

        return -1;
    }

    glfwSetFramebufferSizeCallback(window, WindowManager::framebuffer_size_callback);

    Shader shader("../shaders/shader.vs", "../shaders/shader.fs");

    GLuint textureID = TextureManager::LoadTexture("../textures/blocks/grass.png");
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glEnable(GL_DEPTH_TEST);
    
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    if(glfwRawMouseMotionSupported()) {
        glfwSetInputMode(window, GLFW_RAW_MOUSE_MOTION, GLFW_TRUE);
    }


    shader.use();
    shader.setInt("texture1", 0);

    camera.Position = glm::vec3(0.0f, 0.0f, 3.0f);

    Chunk chunk({0, 0, 0});  // Create chunk at world chunk coords (0,0,0)
    chunk.generateTerrain(); // Generate voxel data inside that chunk

    Mesh mesh({}, {});
    chunk.generateMesh(mesh);

    while (!glfwWindowShouldClose(window)) {
    // Update time
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;


    inputManager.ProcessKeyboard(window, deltaTime);

    // Clear screen
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Camera matrices
    glm::mat4 view = camera.GetViewMatrix();
    glm::mat4 projection = glm::perspective(glm::radians(camera.Zoom),
        (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
    glm::mat4 model = glm::mat4(1.0f);

    shader.setMat4("view", view);
    shader.setMat4("projection", projection);
    shader.setMat4("model", model);

    mesh.Draw(textureID);

    glfwSwapBuffers(window);
    glfwPollEvents();

}


    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;

}
