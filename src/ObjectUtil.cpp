#include "ObjectUtil.hpp"

GLfloat* ObjectColor::toArray()
{
    this->rgb[0] = this->r;
    this->rgb[1] = this->g;
    this->rgb[2] = this->b;
    return this->rgb;
}

Quaternion::Quaternion()
    : w_(1.f), x_(0.f), y_(0.f), z_(0.f)
{
    return;
}

Quaternion::Quaternion(const GLfloat& w, const GLfloat& x, const GLfloat& y, const GLfloat& z)
    : w_(w), x_(x), y_(y), z_(z)
{
    return;
}

void Quaternion::set(const GLfloat& w, const GLfloat& x, const GLfloat& y, const GLfloat& z)
{
    this->w_ = w;
    this->x_ = x;
    this->y_ = y;
    this->z_ = z;
    return;
}

void Quaternion::toAngleAxis(GLfloat& angle, GLfloat& x, GLfloat& y, GLfloat& z)
{
    angle = 2 * std::acos(this->w_) * 180 / M_PI;
    GLfloat s = 1 - this->w_ * this->w_;
    if(s > 0.001) {
        x    = this->x_ / std::sqrt(1 - this->w_ * this->w_);
        y    = this->y_ / std::sqrt(1 - this->w_ * this->w_);
        z    = this->z_ / std::sqrt(1 - this->w_ * this->w_);
        return;
    } else {
        x_ = 1;
        y_ = 0;
        z_ = 0;
        return;
    }
}

void Quaternion::toGLAngleAxis(GLfloat& angle, GLfloat& x, GLfloat& y, GLfloat& z)
{
    angle = 2 * std::acos(this->w_) * 180 / M_PI;
    GLfloat s = 1 - this->w_ * this->w_;
    if(s > 0.001) {
        x    = this->x_ / std::sqrt(1 - this->w_ * this->w_);
        y    = this->z_ / std::sqrt(1 - this->w_ * this->w_);
        z    = this->y_ / std::sqrt(1 - this->w_ * this->w_);
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
    this->w_ = std::cos(angle * M_PI / 2 / 180.f);
    this->x_ = x / s;
    this->y_ = y / s;
    this->z_ = z / s;
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
