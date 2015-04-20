#pragma once
#include <GL/freeglut.h>
#include <cmath>
#define _USE_MATH_DEFINES

class Point
{
public:
    GLdouble x{0.0};
    GLdouble y{0.0};
    GLdouble z{0.0};
    Point() = default;
    Point(GLdouble x, GLdouble y, GLdouble z) : x(x), y(y), z(z) {};
    void set(const GLdouble& x, const GLdouble& y, const GLdouble& z);
};

class ObjectColor
{
public:
    GLfloat r {1.f};
    GLfloat g {1.f};
    GLfloat b {1.f};
    GLfloat rgb[3];
    ObjectColor() = default;
    ObjectColor(GLfloat r, GLfloat g, GLfloat b) : r(r), g(g), b(b) {}
    GLfloat* toArray();
};

class Quaternion
{
public:
    GLfloat w, x, y, z;
    Quaternion();
    Quaternion(const GLfloat& w, const GLfloat& x, const GLfloat& y, const GLfloat& z);
    virtual ~Quaternion() = default;
    void set(const GLfloat& w, const GLfloat& x, const GLfloat& y, const GLfloat& z);
    void toAngleAxis(GLfloat& angle, GLfloat& x, GLfloat& y, GLfloat& z);
    void toGLAngleAxis(GLfloat& angle, GLfloat& x, GLfloat& y, GLfloat& z);
    void fromAngleAxis(const GLfloat& angle, const GLfloat& x,const GLfloat& y,const GLfloat& z);
};
