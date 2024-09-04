#include "Texture.h"

#include "stb_image.h"
#include <iostream>

Texture::Texture(const std::string& path) 
    : m_RendererID(0), m_FilePath(path), m_LocalBuffer(nullptr), m_Width(0), m_Height(0), m_BPP(0)
{

    // Flip the image upside down (OpenGL expects image to start at bottom left corner)
    stbi_set_flip_vertically_on_load(1);
    // load image and gets its dimensions + BPP
    m_LocalBuffer = stbi_load(path.c_str(), &m_Width, &m_Height, &m_BPP, 4 /*define how many channels RGBA*/);


    // Create Texture
    GLCall(glGenTextures(1, &m_RendererID));
    // Bind the texture
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));

    // Set settings for the texture 
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE));
    GLCall(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE));



    // TODO: Read documentation
    GLCall(glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA8 /*specify bits per channel*/,m_Width, m_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_LocalBuffer));
    Unbind();

    if (m_LocalBuffer)
        stbi_image_free(m_LocalBuffer);
}


Texture::~Texture() { GLCall(glDeleteTextures(1, &m_RendererID)); }


void Texture::Bind(unsigned int slot) const 
{
    GLCall(glActiveTexture(GL_TEXTURE0 + slot));
    GLCall(glBindTexture(GL_TEXTURE_2D, m_RendererID));
}

void Texture::Unbind() const 
{
    GLCall(glBindTexture(GL_TEXTURE_2D, 0));
}
