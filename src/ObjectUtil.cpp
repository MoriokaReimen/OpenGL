#include "ObjectUtil.hpp"

void Point::set(const GLdouble& x, const GLdouble& y, const GLdouble& z)
{
  this->x = x;
  this->y = y;
  this->z = z;
  return;
}

GLfloat* ObjectColor::toArray()
{
    this->rgb[0] = this->r;
    this->rgb[1] = this->g;
    this->rgb[2] = this->b;
    return this->rgb;
}

Quaternion::Quaternion()
    : w(1.f), x(0.f), y(0.f), z(0.f)
{
    return;
}

Quaternion::Quaternion(const GLfloat& w, const GLfloat& x, const GLfloat& y, const GLfloat& z)
    : w(w), x(x), y(y), z(z)
{
    return;
}

void Quaternion::set(const GLfloat& w, const GLfloat& x, const GLfloat& y, const GLfloat& z)
{
    this->w = w;
    this->x = x;
    this->y = y;
    this->z = z;
    return;
}

void Quaternion::toAngleAxis(GLfloat& angle, GLfloat& x, GLfloat& y, GLfloat& z)
{
    angle = 2 * std::acos(this->w) * 180 / M_PI;
    GLfloat s = 1 - this->w * this->w;
    if(s > 0.001) {
        x    = this->x / std::sqrt(1 - this->w * this->w);
        y    = this->y / std::sqrt(1 - this->w * this->w);
        z    = this->z / std::sqrt(1 - this->w * this->w);
        return;
    } else {
        x = 1;
        y = 0;
        z = 0;
        return;
    }
}

void Quaternion::toGLAngleAxis(GLfloat& angle, GLfloat& x, GLfloat& y, GLfloat& z)
{
    angle = 2 * std::acos(this->w) * 180 / M_PI;
    GLfloat s = 1 - this->w * this->w;
    if(s > 0.001) {
        x    = this->x / std::sqrt(1 - this->w * this->w);
        y    = this->z / std::sqrt(1 - this->w * this->w);
        z    = this->y / std::sqrt(1 - this->w * this->w);
        return;
    } else {
        x = 1;
        y = 0;
        z = 0;
        return;
    }
}

void Quaternion::fromAngleAxis(const GLfloat& angle, const GLfloat& x,const GLfloat& y,const GLfloat& z)
{
    GLfloat s = std::sin(angle * M_PI / 2 / 180.f);
    this->w = std::cos(angle * M_PI / 2 / 180.f);
    this->x = x / s;
    this->y = y / s;
    this->z = z / s;
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
