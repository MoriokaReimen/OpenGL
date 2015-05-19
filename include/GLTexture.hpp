#pragma once
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<string>
#include<SOIL/SOIL.h>
#include "PNG.hpp"

typedef unsigned char ubyte_t;
class GLTexture
{
    std::string filename;
    GLuint id; // texture id for gl
public:
    GLTexture();
    GLTexture(const std::string& filename);
    GLTexture(const PNG& png);
    ~GLTexture();
    GLuint getID();
};
