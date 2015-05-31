#include "ObjectColor.hpp"

GLfloat* ObjectColor::toArray()
{
    this->rgb[0] = this->r;
    this->rgb[1] = this->g;
    this->rgb[2] = this->b;
    return this->rgb;
}
