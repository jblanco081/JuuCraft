#include <Mesh.h>
#include <FaceDirection.h>

#include <glad/glad.h>
#include <array>
#include <iostream>

namespace {
void addFace(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices,
                 glm::vec3 blockPos, glm::vec3 faceNormal,
                 const std::array<glm::vec3, 4>& faceVertices,
                 glm::vec2 uvTopLeft, glm::vec2 uvBottomRight,
                 unsigned int& indexOffset) {
        
        glm::vec2 uvTopRight = { uvBottomRight.x, uvTopLeft.y };
        glm::vec2 uvBottomLeft = { uvTopLeft.x, uvBottomRight.y };

        vertices.push_back({ blockPos + faceVertices[0], faceNormal, uvTopLeft });
        vertices.push_back({ blockPos + faceVertices[1], faceNormal, uvBottomLeft });
        vertices.push_back({ blockPos + faceVertices[2], faceNormal, uvBottomRight });
        vertices.push_back({ blockPos + faceVertices[3], faceNormal, uvTopRight });

        indices.push_back(indexOffset);
        indices.push_back(indexOffset + 1);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset);
        indices.push_back(indexOffset + 2);
        indices.push_back(indexOffset + 3);

        indexOffset += 4;
    }
}

// Each face of the cube (in local space)
const std::array<glm::vec3, 4> FRONT = {
    glm::vec3(0, 1, 1),
    glm::vec3(0, 0, 1),
    glm::vec3(1, 0, 1),
    glm::vec3(1, 1, 1)
};

const glm::vec3 NORMAL_FRONT = glm::vec3(0, 0, 1);

// Back face
const std::array<glm::vec3, 4> BACK = {
    glm::vec3(1, 1, 0),
    glm::vec3(1, 0, 0),
    glm::vec3(0, 0, 0),
    glm::vec3(0, 1, 0)
};
const glm::vec3 NORMAL_BACK = glm::vec3(0, 0, -1);

// Left face
const std::array<glm::vec3, 4> LEFT = {
    glm::vec3(0, 1, 0),
    glm::vec3(0, 0, 0),
    glm::vec3(0, 0, 1),
    glm::vec3(0, 1, 1)
};
const glm::vec3 NORMAL_LEFT = glm::vec3(-1, 0, 0);

// Right face
const std::array<glm::vec3, 4> RIGHT = {
    glm::vec3(1, 1, 1),
    glm::vec3(1, 0, 1),
    glm::vec3(1, 0, 0),
    glm::vec3(1, 1, 0)
};
const glm::vec3 NORMAL_RIGHT = glm::vec3(1, 0, 0);

// Top face
const std::array<glm::vec3, 4> TOP = {
    glm::vec3(0, 1, 0),
    glm::vec3(0, 1, 1),
    glm::vec3(1, 1, 1),
    glm::vec3(1, 1, 0)
};
const glm::vec3 NORMAL_TOP = glm::vec3(0, 1, 0);

// Bottom face
const std::array<glm::vec3, 4> BOTTOM = {
    glm::vec3(0, 0, 1),
    glm::vec3(0, 0, 0),
    glm::vec3(1, 0, 0),
    glm::vec3(1, 0, 1)
};
const glm::vec3 NORMAL_BOTTOM = glm::vec3(0, -1, 0);

Mesh::Mesh(std::vector<Vertex> vertices, std::vector<unsigned int> indices) 
: vertices(vertices), indices(indices) {
    setupMesh();

}

void Mesh::setupMesh() {
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);

    glBindVertexArray(VAO);

    // Load vertex data
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(Vertex),
                    &vertices[0], GL_STATIC_DRAW);

    // Load index data
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int),
                    &indices[0], GL_STATIC_DRAW);

    // Position
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (void*)0);
    glEnableVertexAttribArray(0);

    // Normal
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (void*)offsetof(Vertex, normal));
    glEnableVertexAttribArray(1);

    // Texture Coordinates
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex),
                            (void*)offsetof(Vertex, texCoords));
    glEnableVertexAttribArray(2);

    glBindVertexArray(0);
}

void Mesh::Draw(unsigned int textureID) {
    glBindTexture(GL_TEXTURE_2D, textureID);
    glBindVertexArray(VAO);
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
} 

void Mesh::PrintVertexData() {
    for (const auto& v : vertices) {
        std::cout << "Pos: " << v.position.x << ", " << v.position.y << ", " << v.position.z << '\n';
    }
}

void Mesh::addFace(glm::vec3 blockPos, FaceDirection face) {
    // Example switch-case for face data
    const std::array<glm::vec3, 4>* faceVertices = nullptr;
    glm::vec3 faceNormal;

    switch (face) {
        case FaceDirection::FD_FRONT: faceVertices = &FRONT; faceNormal = NORMAL_FRONT; break;
        case FaceDirection::FD_BACK: faceVertices = &BACK; faceNormal = NORMAL_BACK; break;
        case FaceDirection::FD_LEFT: faceVertices = &LEFT; faceNormal = NORMAL_LEFT; break;
        case FaceDirection::FD_RIGHT: faceVertices = &RIGHT; faceNormal = NORMAL_RIGHT; break;
        case FaceDirection::FD_TOP: faceVertices = &TOP; faceNormal = NORMAL_TOP; break;
        case FaceDirection::FD_BOTTOM: faceVertices = &BOTTOM; faceNormal = NORMAL_BOTTOM; break;
    }

    glm::vec2 uvTopLeft(0.0f, 1.0f);
    glm::vec2 uvBottomRight(1.0f, 0.0f);

    ::addFace(vertices, indices, blockPos, faceNormal, *faceVertices, uvTopLeft, uvBottomRight, indexOffset);
}
