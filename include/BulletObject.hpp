#pragma once

#include <memory>
#include <exception>
#include <btBulletDynamicsCommon.h>
#include "3dMath.hpp"

class BulletObject
{
  btRigidBody* body_;
  btCollisionShape* shape_;
public:
  BulletObject(btRigidBody* body, btCollisionShape* shape);
  ~BulletObject();
  Point getPoint();
  Quaternion getQuat();
  btRigidBody* getBody();
};

typedef std::shared_ptr<BulletObject> pBulletObject;

class BulletObjectFactory
{
public:
  static btScalar mass;
  static Point xyz;
  static Quaternion quat;
  static pBulletObject spawnSphere(double radius);
  static pBulletObject spawnStaticPlane();
};
