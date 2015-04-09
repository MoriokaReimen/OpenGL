#pragma once
#include <GL/freeglut.h>
#include "ObjectUtil.hpp"


class Object
{
protected:
  Point xyz{0, 0, 0};
  // Attitude attitude; implement someday
  ObjectColor color{0,0,0};
public:
  Object(){}
  virtual ~Object() = default;
  virtual void draw() = 0;
  virtual void setPosition(double x, double y, double z);
  virtual void setPosition(Point point);
  virtual void setColor(ObjectColor bcolor);
  virtual void setColor(GLfloat br, GLfloat bg, GLfloat bb);
  // virtual void setAttitude() = 0; implement someday
};

class Sphere : public Object
{
protected:
public:
  void draw() override; // protect someday
};

class Cube : public Object
{
protected:
public:
  void draw() override; // protect someday
};

class Floor : public Object
{
public:
  void draw() override; // protect someday
};

class Axis : public Object
{
public:
  void draw();
};
