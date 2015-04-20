#pragma once
#include "GLFW.hpp"
#include "BulletObject.hpp"

#include <btBulletDynamicsCommon.h>

class BulletGLFW : public GLFW
{
  btBroadphaseInterface* broadphase_;
  btDefaultCollisionConfiguration* collision_config_;
  btCollisionDispatcher* dispatcher_;
  btSequentialImpulseConstraintSolver* solver_;
  btDiscreteDynamicsWorld* world_;
  double gravity_{9.80665};
public:
  BulletGLFW();
  virtual ~BulletGLFW();
  virtual void run() override;
  void pushObject(pBulletObject object)
  {
    GLFW::pushObject(object);
    this->world_->addRigidBody(object->getRigidBody());
    return;
  }
};

