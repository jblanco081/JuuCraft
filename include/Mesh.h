#ifndef MESH_H
#define MESH_H

#include <vector>
#include <glm/glm.hpp>

#include "FaceDirection.h"


struct Vertex {
    glm::vec3 position;
    glm::vec3 normal;
    glm::vec2 texCoords;
};

class Mesh {
public:
    Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices);
    void Draw(unsigned int textureID);
    void PrintVertexData();
    void addFace(glm::vec3 position, FaceDirection face); 

    ~Mesh();

private:
    std::vector<Vertex> vertices;
    std::vector<unsigned int> indices;
    unsigned int VAO, VBO, EBO;
    unsigned int indexOffset = 0;


    void setupMesh();
};

#endif
