#pragma once

#include <memory>
#include <exception>
#include <btBulletDynamicsCommon.h>
#include "ObjectUtil.hpp"

class BaseBulletObject
{
  btRigidBody* body_;
  btCollisionShape* shape_;
public:
  BaseBulletObject(btRigidBody* body, btCollisionShape* shape);
  ~BaseBulletObject();
  Point getPoint();
  Quaternion getQuat();
  btRigidBody* getBody();
};

typedef std::shared_ptr<BaseBulletObject> pBaseBulletObject;

class BaseBulletObjectFactory
{
public:
  static btScalar mass;
  static Point xyz;
  static Quaternion quat;
  static pBaseBulletObject spawnSphere(double radius);
  static pBaseBulletObject spawnStaticPlane();
};

