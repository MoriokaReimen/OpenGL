#include"Texture.hpp"

Texture::Texture()
{
}

Texture::Texture(const std::string& fname)
  : filename(fname)
{
    // Load graphic
    this -> id[0] = SOIL_load_OGL_texture(
          filename.c_str(),
          SOIL_LOAD_AUTO,
          SOIL_CREATE_NEW_ID,
          SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y | SOIL_FLAG_NTSC_SAFE_RGB | SOIL_FLAG_COMPRESS_TO_DXT
        );
    //if(!id) throw;

    // register texture
    glBindTexture(GL_TEXTURE_2D, id[0]);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}

Texture::~Texture()
{
}

unsigned int Texture::getID()
{ return id[0]; }
