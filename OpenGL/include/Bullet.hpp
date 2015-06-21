#pragma once
#include "BulletObject.hpp"
#include <btBulletDynamicsCommon.h>
#include <list>

class Bullet
{
  std::list<BulletObject*> object_list_;
  btBroadphaseInterface* broadphase_;
  btDefaultCollisionConfiguration* collision_config_;
  btCollisionDispatcher* dispatcher_;
  btSequentialImpulseConstraintSolver* solver_;
  btDiscreteDynamicsWorld* world_;
public:
  double time{0.0};
  Bullet();
  virtual ~Bullet();
  virtual void step();
  void pushObject(BulletObject* object);
};

