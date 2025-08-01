#pragma once

#include <array>
#include <glm/glm.hpp>

#include <Mesh.h>
#include <FaceDirection.h>

enum VoxelType : uint8_t {
    AIR = 0,
    DIRT = 1,
    STONE = 2,
};

constexpr int CHUNK_SIZE = 16;

struct Voxel {
    VoxelType type = AIR;

};

class Chunk {
public:
    Chunk(glm::ivec3 chunkPosition);
    
    void generateTerrain();
    Voxel getVoxel(int x, int y, int z) const;
    void setVoxel(int x, int y, int z, VoxelType type);
    void generateMesh(Mesh& mesh);
    glm::ivec3 getChunkPosition() const;

private:
    glm::ivec3 m_chunkPosition;
    std::array<std::array<std::array<Voxel, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> m_voxels;
};

