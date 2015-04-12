#pragma once
#include<GL/gl.h>
#include<GL/glu.h>
#include<GL/glut.h>
#include<string>
#include<SOIL/SOIL.h>

typedef unsigned char ubyte_t;
class Texture
{
    std::string filename;
    GLuint id{0}; // texture id for gl 
public:
    Texture(const std::string& filename);
    ~Texture();
    unsigned int getID();
};
