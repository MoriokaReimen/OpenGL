#pragma once
#include <GL/freeglut.h>
#include <cmath>
#define _USE_MATH_DEFINES

class Point
{
public:
    GLdouble x {0.0};
    GLdouble y {0.0};
    GLdouble z {0.0};
    Point() = default;
    Point(GLdouble bx, GLdouble by, GLdouble bz) : x(bx), y(by), z(bz) {};
};

class ObjectColor
{
public:
    GLfloat r {1.f};
    GLfloat g {1.f};
    GLfloat b {1.f};
    GLfloat rgb[3];
    ObjectColor() = default;
    ObjectColor(GLfloat br, GLfloat bg, GLfloat bb) : r(br), g(bg), b(bb) {}
    GLfloat* toArray();
};

class Quaternion
{
    GLfloat w, x, y, z;
public:
    Quaternion();
    Quaternion(const GLfloat& bw, const GLfloat& bx, const GLfloat& by, const GLfloat& bz);
    virtual ~Quaternion() = default;
    void set(const GLfloat& bw, const GLfloat& bx, const GLfloat& by, const GLfloat& bz);
    void toAngleAxis(GLfloat& angle, GLfloat& bx, GLfloat& by, GLfloat& bz);
    void toGLAngleAxis(GLfloat& angle, GLfloat& bx, GLfloat& by, GLfloat& bz);
    void fromAngleAxis(const GLfloat& angle, const GLfloat& bx,const GLfloat& by,const GLfloat& bz);
};
