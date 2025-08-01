#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

#include <string>

class TextureManager {
public:
    static unsigned int LoadTexture(const std::string& path);
};

#endif
