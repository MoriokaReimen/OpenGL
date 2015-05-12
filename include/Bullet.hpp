#pragma once
#include "BulletObject.hpp"
#include <btBulletDynamicsCommon.h>
#include <list>

class Bullet
{
  std::list<pBulletObject> object_list_;
  btBroadphaseInterface* broadphase_;
  btDefaultCollisionConfiguration* collision_config_;
  btCollisionDispatcher* dispatcher_;
  btSequentialImpulseConstraintSolver* solver_;
  btDiscreteDynamicsWorld* world_;
  double gravity_{9.80665};
public:
  Bullet();
  virtual ~Bullet();
  virtual void step();
  void pushObject(pBulletObject object);
};

