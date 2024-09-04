#pragma once

#include <GL/glew.h>

#include "stb_image.h"


class Texture
{

 public:
    Texture() : textureID(0), width(0), height(0), bitDepth(0), fileLocation("") {};
    Texture(const char* fileLocation) : textureID(0), width(0), height(0), bitDepth(0), fileLocation(fileLocation) {};
    ~Texture() {ClearTexture();};
    
 public: 
    void LoadTexture();
    void UseTexture();
    void ClearTexture();

 private:
    GLuint textureID;
    int width, height, bitDepth /*bpp*/;

    const char* fileLocation;
};