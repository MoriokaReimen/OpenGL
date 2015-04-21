#pragma once
#include "BaseBulletObject.hpp"
#include <btBulletDynamicsCommon.h>
#include <list>

class BaseBullet
{
  std::list<pBaseBulletObject> object_list_;
  btBroadphaseInterface* broadphase_;
  btDefaultCollisionConfiguration* collision_config_;
  btCollisionDispatcher* dispatcher_;
  btSequentialImpulseConstraintSolver* solver_;
  btDiscreteDynamicsWorld* world_;
  double gravity_{9.80665};
public:
  BaseBullet();
  virtual ~BaseBullet();
  virtual void step();
  void pushObject(pBaseBulletObject object);
};

