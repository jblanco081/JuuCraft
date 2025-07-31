#pragma once

#include <array>
#include <glm/glm.hpp>

// Voxel types (expand as needed)
enum VoxelType : uint8_t {
    AIR = 0,
    DIRT = 1,
    STONE = 2,
    // Add more voxel types here...
};

constexpr int CHUNK_SIZE = 16;

struct Voxel {
    VoxelType type = AIR;
    // You can add lighting, metadata, etc. here later
};

class Chunk {
public:
    Chunk(glm::ivec3 chunkPosition);
    
    void generateTerrain(); // basic terrain generation
    Voxel getVoxel(int x, int y, int z) const;
    void setVoxel(int x, int y, int z, VoxelType type);

    glm::ivec3 getChunkPosition() const;

private:
    glm::ivec3 m_chunkPosition; // chunk grid coords
    std::array<std::array<std::array<Voxel, CHUNK_SIZE>, CHUNK_SIZE>, CHUNK_SIZE> m_voxels;
};

