#include "Chunk.h"
#include "Mesh.h"
#include "FaceDirection.h"

#include <algorithm>
#include <cmath>


Chunk::Chunk(glm::ivec3 chunkPosition) : m_chunkPosition(chunkPosition) {
    // Initialize all voxels to AIR
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {
                m_voxels[x][y][z].type = AIR;
            }
        }
    }
}

Voxel Chunk::getVoxel(int x, int y, int z) const {
    if (x < 0 || x >= CHUNK_SIZE ||
        y < 0 || y >= CHUNK_SIZE ||
        z < 0 || z >= CHUNK_SIZE) {
        // Out of bounds - return air or handle differently
        return Voxel{ AIR };
    }
    return m_voxels[x][y][z];
}

void Chunk::setVoxel(int x, int y, int z, VoxelType type) {
    if (x < 0 || x >= CHUNK_SIZE ||
        y < 0 || y >= CHUNK_SIZE ||
        z < 0 || z >= CHUNK_SIZE) {
        return; // Out of bounds
    }
    m_voxels[x][y][z].type = type;
}

glm::ivec3 Chunk::getChunkPosition() const {
    return m_chunkPosition;
}

void Chunk::generateTerrain() {
    // Simple flat terrain example:
    // Let's say ground level at y=8, fill below with dirt, above with air

    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int z = 0; z < CHUNK_SIZE; z++) {
            // Calculate world position for noise input
            int worldX = m_chunkPosition.x * CHUNK_SIZE + x;
            int worldZ = m_chunkPosition.z * CHUNK_SIZE + z;

            // Simple flat terrain height - replace with noise function later
            int height = 8; 

            for (int y = 0; y < CHUNK_SIZE; y++) {
                int worldY = m_chunkPosition.y * CHUNK_SIZE + y;
                if (worldY <= height) {
                    setVoxel(x, y, z, DIRT);
                } else {
                    setVoxel(x, y, z, AIR);
                }
            }
        }
    }
}

void Chunk::generateMesh(Mesh& mesh) {
    for (int x = 0; x < CHUNK_SIZE; x++) {
        for (int y = 0; y < CHUNK_SIZE; y++) {
            for (int z = 0; z < CHUNK_SIZE; z++) {

                if (getVoxel(x, y, z).type == AIR) continue;

                glm::vec3 blockPos = glm::vec3(
                    x + m_chunkPosition.x * CHUNK_SIZE,
                    y + m_chunkPosition.y * CHUNK_SIZE,
                    z + m_chunkPosition.z * CHUNK_SIZE
                );

                // FRONT
                if (getVoxel(x, y, z + 1).type == AIR)
                    mesh.addFace(blockPos, FaceDirection::FD_FRONT);

                // BACK
                if (getVoxel(x, y, z - 1).type == AIR)
                    mesh.addFace(blockPos, FaceDirection::FD_BACK);

                // LEFT
                if (getVoxel(x - 1, y, z).type == AIR)
                    mesh.addFace(blockPos, FaceDirection::FD_LEFT);

                // RIGHT
                if (getVoxel(x + 1, y, z).type == AIR)
                    mesh.addFace(blockPos, FaceDirection::FD_RIGHT);

                // TOP
                if (getVoxel(x, y + 1, z).type == AIR)
                    mesh.addFace(blockPos, FaceDirection::FD_TOP);

                // BOTTOM
                if (getVoxel(x, y - 1, z).type == AIR)
                    mesh.addFace(blockPos, FaceDirection::FD_BOTTOM);
            }
        }
    }
}
