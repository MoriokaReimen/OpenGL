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
  Quaternion()
    : w(0.f), x(0.f), y(0.f), z(0.f)
  {
    return;
  }

  Quaternion(const GLfloat& bw, const GLfloat& bx, const GLfloat& by, const GLfloat& bz)
    : w(bw), x(bx), y(by), z(bz)
  {
    return;
  }

  virtual ~Quaternion() = default;

  void set(const GLfloat& bw, const GLfloat& bx, const GLfloat& by, const GLfloat& bz)
  {
    w = bw;
    x = bx;
    y = by;
    z = bz;
    return;
  }

  /* implement someday
  void toMat(GLfloat* mat)
  {
    mat[0] = w * w + x * x - y * y - z * z;
    mat[1] = 2 * (x * y + w * z);
    mat[2] = 2 * (x * z - w * y);
    mat[3] = 2 * (x * z - w * y);
  }
  */

  void toAngleAxis(GLfloat& bx, GLfloat& by, GLfloat& bz, GLfloat& angle)
  {
    angle = 2 * std::acos(this->w) * 180 / M_PI;
    GLfloat s = 1 - this->w * this->w;
    if(s > 0.001)
    {
      bx    = this->x / std::sqrt(1 - this->w * this->w);
      bx    = this->y / std::sqrt(1 - this->w * this->w);
      bx    = this->z / std::sqrt(1 - this->w * this->w);
      return;
    }
    else {
      bx = 1;
      by = 0;
      bz = 0;
      return;
    }
  }
};
