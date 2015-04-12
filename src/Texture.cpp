#include"Texture.hpp"

Texture::Texture(const std::string& fname)
  : filename(fname)
{
    // Load graphic
    this -> id = SOIL_load_OGL_texture(
          filename.c_str(),
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_INVERT_Y
        );
    if(!id) throw;

    // register texture
    glBindTexture(GL_TEXTURE_2D, id);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
}

unsigned int Texture::getID()
{ return id; }
