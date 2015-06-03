#pragma once

#include <memory>
#include <exception>
#include <btBulletDynamicsCommon.h>
#include <Math3D/Math3D.hpp>
#include "ObjectColor.hpp"

class BulletObject
{
  btRigidBody* body_;
  btCollisionShape* shape_;
public:
  BulletObject(btRigidBody* body, btCollisionShape* shape);
  ~BulletObject();
  Math3D::Vector3 getPoint();
  Math3D::Quaternion getQuat();
  btRigidBody* getBody();
};

typedef std::shared_ptr<BulletObject> pBulletObject;

class BulletObjectFactory
{
public:
  static btScalar mass;
  static Math3D::Vector3 xyz;
  static Math3D::Quaternion quat;
  static pBulletObject spawnSphere(double radius);
  static pBulletObject spawnStaticPlane();
};
