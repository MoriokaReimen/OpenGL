#include "ObjectUtil.hpp"

GLfloat* ObjectColor::toArray()
{
  rgb[0] = this->r;
  rgb[1] = this->g;
  rgb[2] = this->b;
  return rgb;
}
