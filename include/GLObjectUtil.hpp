#pragma once
#include <GL/freeglut.h>
#include <cmath>
#define _USE_MATH_DEFINES

class GLPoint
{
public:
    GLdouble x{0.0};
    GLdouble y{0.0};
    GLdouble z{0.0};
    GLPoint() = default;
    GLPoint(GLdouble x, GLdouble y, GLdouble z) : x(x), y(y), z(z) {};
    void set(const GLdouble& x, const GLdouble& y, const GLdouble& z);
};

class ObjectColor
{
public:
    GLfloat r {1.f};
    GLfloat g {1.f};
    GLfloat b {1.f};
    GLfloat rgb[3];
    GLObjectColor() = default;
    GLObjectColor(GLfloat r, GLfloat g, GLfloat b) : r(r), g(g), b(b) {}
    GLfloat* toArray();
};

class GLQuaternion
{
public:
    GLfloat w, x, y, z;
    GLQuaternion();
    GLQuaternion(const GLfloat& w, const GLfloat& x, const GLfloat& y, const GLfloat& z);
    virtual ~GLQuaternion() = default;
    void set(const GLfloat& w, const GLfloat& x, const GLfloat& y, const GLfloat& z);
    void toAngleAxis(GLfloat& angle, GLfloat& x, GLfloat& y, GLfloat& z);
    void toGLAngleAxis(GLfloat& angle, GLfloat& x, GLfloat& y, GLfloat& z);
    void fromAngleAxis(const GLfloat& angle, const GLfloat& x,const GLfloat& y,const GLfloat& z);
};
