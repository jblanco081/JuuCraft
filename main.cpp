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
#include "Config.h"

// camera
Camera camera;
InputManager inputManager(camera, SCR_WIDTH, SCR_HEIGHT);

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

int main() {

    GLFWwindow* window = WindowManager::Init(SCR_WIDTH, SCR_HEIGHT, "JuuCraft");
    
    Shader shader("../shaders/shader.vs", "../shaders/shader.fs");

    GLuint textureID = TextureManager::LoadTexture("../textures/blocks/grass.png");
    
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureID);
        
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
