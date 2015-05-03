#pragma once
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<string>
#include<SOIL/SOIL.h>

typedef unsigned char ubyte_t;
class GLTexture
{
    std::string filename;
    GLuint id; // texture id for gl
public:
    GLTexture();
    GLTexture(const std::string& filename);
    ~GLTexture();
    GLuint getID();
};
