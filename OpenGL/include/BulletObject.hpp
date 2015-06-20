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
    void setPosition(const Math3D::Vector3& pos);
    void setAttitude(const Math3D::Quaternion& quat);
};

class BulletSphere : public BulletObject
{
public:
    BulletSphere(const Math3D::Vector3& xyz, const Math3D::Quaternion& quat, const double& mass, const double& radius);
};

class BulletPlane : public BulletObject
{
public:
    BulletPlane(const Math3D::Vector3& xyz, const Math3D::Quaternion& quat);
};
