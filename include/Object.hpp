#pragma once
#include "ObjectUtil.hpp"
#include "Texture.hpp"
#include <memory>


class Object
{
protected:
    Point xyz_ {0, 0, 0};
    // Attitude attitude; implement someday
    ObjectColor color_ {1.f,1.f,1.f};
    Texture texture_;
    Quaternion quat_{1.f, 0.f, 0.f, 0.f};
public:
    Object() = default;
    virtual ~Object() = default;
    virtual void draw() {};
    virtual void setPosition(double x, double y, double z);
    virtual void setPosition(Point point);
    virtual void setColor(ObjectColor bcolor);
    virtual void setColor(GLfloat r, GLfloat g, GLfloat b);
    virtual void setTexture(Texture& texture);
    virtual void setAttitude(const Quaternion& quat);
};

class Sphere : public Object
{
protected:
  GLfloat radius_{10};
public:
    virtual void draw() override; // protect someday
    virtual void setSize(const GLfloat& bradius);
};

class Cube : public Object
{
protected:
  GLfloat a_{10};
  GLfloat b_{10};
  GLfloat c_{10};
public:
    virtual void draw() override; // protect someday
    virtual void setSize(const GLfloat& a, const GLfloat& b, const GLfloat& c);
};

class Floor : public Object
{
protected:
  GLfloat a_{10};
  GLfloat b_{10};
public:
    virtual void draw() override; // protect someday
    virtual void setSize(const GLfloat& a, const GLfloat& b);
};

class Axis : public Object
{
protected:
  GLfloat width_{10};
  GLfloat length_{10};
public:
    virtual void draw() override;
    virtual void setSize(const GLfloat& width, const GLfloat& length);
};

class Cylinder : public Object
{
  GLfloat radius_{10};
  GLfloat height_{10};
public:
    virtual void draw() override;
    virtual void setSize(const GLfloat& radius, const GLfloat& height);
};

typedef std::shared_ptr<Sphere> pSphere;
typedef std::shared_ptr<Object> pObject;
typedef std::shared_ptr<Floor> pFloor;
typedef std::shared_ptr<Axis> pAxis;
typedef std::shared_ptr<Cylinder> pCylinder;
typedef std::shared_ptr<Cube> pCube;
