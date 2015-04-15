#include "ObjectUtil.hpp"

GLfloat* ObjectColor::toArray()
{
    rgb[0] = this->r;
    rgb[1] = this->g;
    rgb[2] = this->b;
    return rgb;
}

Quaternion::Quaternion()
  : w(0.f), x(0.f), y(0.f), z(0.f)
{
  return;
}

Quaternion::Quaternion(const GLfloat& bw, const GLfloat& bx, const GLfloat& by, const GLfloat& bz)
  : w(bw), x(bx), y(by), z(bz)
{
  return;
}

void Quaternion::set(const GLfloat& bw, const GLfloat& bx, const GLfloat& by, const GLfloat& bz)
{
  w = bw;
  x = bx;
  y = by;
  z = bz;
  return;
}

void Quaternion::toAxisAngle(GLfloat& bx, GLfloat& by, GLfloat& bz, GLfloat& angle)
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

void Quaternion::fromAxisAngle(const GLfloat& bx,const GLfloat& by,const GLfloat& bz,const GLfloat& angle)
{
  GLfloat s = std::sin(angle * M_PI / 2 / 180.f);
  this->w = std::cos(angle * M_PI / 2 / 180.f);
  this->x = bx / s;
  this->y = by / s;
  this->z = bz / s;
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
