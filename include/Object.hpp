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
