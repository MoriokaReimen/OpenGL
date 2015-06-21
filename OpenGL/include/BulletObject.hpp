#pragma once

#include <memory>
#include <exception>
#include <btBulletDynamicsCommon.h>
#include <Math3D/Math3D.hpp>
#include "GLColor.hpp"

class BulletObject
{
protected:
  btRigidBody* body_;
  btCollisionShape* shape_;
public:
  ~BulletObject();
  Math3D::Vector3 getPosition();
  Math3D::Quaternion getAttitude();
  btRigidBody* getBody();
    void setPosition(const Math3D::Vector3& pos);
    void setAttitude(const Math3D::Quaternion& quat);
};

class BulletSphere : public BulletObject
{
public:
    BulletSphere(const double& mass, const double& radius);
};

class BulletPlane : public BulletObject
{
public:
    BulletPlane();
};

class BulletBox : public BulletObject
{
public:
    BulletBox(const double& mass, const double& a, const double& b, const double c);
};
