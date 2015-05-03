#pragma once

#include <memory>
#include <exception>
#include <btBulletDynamicsCommon.h>
#include "GLObjectUtil.hpp"

class BulletObject
{
  btRigidBody* body_;
  btCollisionShape* shape_;
public:
  BulletObject(btRigidBody* body, btCollisionShape* shape);
  ~BulletObject();
  GLPoint getPoint();
  GLQuaternion getQuat();
  btRigidBody* getBody();
};

typedef std::shared_ptr<BulletObject> pBulletObject;

class BulletObjectFactory
{
public:
  static btScalar mass;
  static GLPoint xyz;
  static GLQuaternion quat;
  static pBulletObject spawnSphere(double radius);
  static pBulletObject spawnStaticPlane();
};

