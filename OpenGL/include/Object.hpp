#pragma once
#include "BulletObject.hpp"
#include "GLObject.hpp"

class Object
{
public:
    GLObject* gl_;
    BulletObject* bullet_;

    virtual ~Object();
    void setPosition(const Math3D::Vector3& xyz);
    void setAttitude(const Math3D::Quaternion& quat);
    virtual void setColor(const GLfloat& r, const GLfloat& g, const GLfloat& b);
    virtual Math3D::Vector3  getPosition();
    virtual Math3D::Quaternion  getAttitude();
    virtual void update();
};

class Sphere : public Object
{
public:
    Sphere(const double& mass, const double& radius);
};

class Plane : public Object
{
public:
    Plane();
};
