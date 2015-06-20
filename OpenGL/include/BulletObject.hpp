#pragma once

#include <memory>
#include <exception>
#include <btBulletDynamicsCommon.h>
#include <Math3D/Math3D.hpp>
#include "ObjectColor.hpp"

class BulletObject
{
protected:
  btRigidBody* body_;
  btCollisionShape* shape_;
public:
  ~BulletObject();
  Math3D::Vector3 getPoint();
  Math3D::Quaternion getQuat();
  btRigidBody* getBody();
    void setPosition(Math3D::Vector3 pos);
    void setAttitude(Math3D::Quaternion quat);
};

class BulletSphere : public BulletObject
{
public:
    BulletSphere(Math3D::Vector3 xyz, Math3D::Quaternion quat, double mass, double radius);
};

class BulletPlane : public BulletObject
{
public:
    BulletPlane(Math3D::Vector3 xyz, Math3D::Quaternion quat);
};
