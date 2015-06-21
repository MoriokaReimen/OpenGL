#pragma once
#include <GL/freeglut.h>
#define _USE_MATH_DEFINES

class GLColor
{
public:
    float r {1.f};
    float g {1.f};
    float b {1.f};
    float rgb[3];
    GLColor() = default;
    GLColor(GLfloat r, GLfloat g, GLfloat b) : r(r), g(g), b(b) {}
    GLfloat* toArray();
};
