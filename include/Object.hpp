#pragma once
#include "ObjectUtil.hpp"
#include "Texture.hpp"
#include <memory>


class Object
{
protected:
    Point xyz {0, 0, 0};
    // Attitude attitude; implement someday
    ObjectColor color {1.f,1.f,1.f};
    Texture texture;
    Quaternion quat{1.f, 0.f, 0.f, 0.f};
public:
    Object() = default;
    virtual ~Object() = default;
    virtual void draw() {};
    virtual void setPosition(double x, double y, double z);
    virtual void setPosition(Point point);
    virtual void setColor(ObjectColor bcolor);
    virtual void setColor(GLfloat br, GLfloat bg, GLfloat bb);
    virtual void setTexture(Texture& texture);
    virtual void setAttitude(const Quaternion& bquat);
};

class Sphere : public Object
{
protected:
  GLfloat radius{10};
public:
    void draw() override; // protect someday
    void setSize(const GLfloat& bradius);
};

class Cube : public Object
{
protected:
  GLfloat a{10};
  GLfloat b{10};
  GLfloat c{10};
public:
    void draw() override; // protect someday
    void setSize(const GLfloat& ba, const GLfloat& bb, const GLfloat& bc);
};

class Floor : public Object
{
protected:
  GLfloat a{10};
  GLfloat b{10};
public:
    void draw() override; // protect someday
    void setSize(const GLfloat& ba, const GLfloat& bb);
};

class Axis : public Object
{
protected:
  GLfloat width{10};
  GLfloat length{10};
public:
    void draw() override;
    void setSize(const GLfloat& bwidth, const GLfloat& blength);
};

class Cylinder : public Object
{
  GLfloat radius{10};
  GLfloat height{10};
public:
    void draw() override;
    void setSize(const GLfloat& bradius, const GLfloat& bheight);
};

typedef std::shared_ptr<Sphere> pSphere;
typedef std::shared_ptr<Object> pObject;
typedef std::shared_ptr<Floor> pFloor;
typedef std::shared_ptr<Axis> pAxis;
typedef std::shared_ptr<Cylinder> pCylinder;
typedef std::shared_ptr<Cube> pCube;
