#include"GLTexture.hpp"
#include <iostream>

GLTexture::GLTexture()
{
}

GLTexture::GLTexture(const std::string& fname)
    : filename(fname)
{
    //glShadeModel(GL_SMOOTH);
    // Load graphic
    id = SOIL_load_OGL_texture(
             filename.c_str(),
             SOIL_LOAD_AUTO,
             SOIL_CREATE_NEW_ID,
             SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
         );
    std::cout << id << std::endl;
    if(!id) throw;

    // register texture
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

GLTexture::GLTexture(const PNG& png)
{
    //glShadeModel(GL_SMOOTH);
    // Load graphic from memory
    id = SOIL_load_OGL_texture_from_memory(
             png.getData(),
             png.getSize(),
             SOIL_LOAD_AUTO,
             SOIL_CREATE_NEW_ID,
             SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
         );
    std::cout << id << std::endl;
    if(!id) throw;

    // register texture
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
}

GLTexture::~GLTexture()
{
}

GLuint GLTexture::getID()
{
    return id;
}
