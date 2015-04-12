#pragma once
#include "ObjectUtil.hpp"
#include <memory>


class Object
{
protected:
    Point xyz {0, 0, 0};
    // Attitude attitude; implement someday
    ObjectColor color {0,0,0};
public:
    Object() = default;
    virtual ~Object() = default;
    virtual void draw() {};
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
    void draw() override;
};

class Cylinder : public Object
{
  GLUquadric* quad;
public:
  Cylinder();
  ~Cylinder();
  void draw() override;
};

typedef std::shared_ptr<Sphere> pSphere;
typedef std::shared_ptr<Object> pObject;
typedef std::shared_ptr<Floor> pFloor;
typedef std::shared_ptr<Axis> pAxis;
typedef std::shared_ptr<Cylinder> pCylinder;
