#pragma once
#include "GLFW.hpp"
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
  ~BulletGLFW();
  virtual void run() override;
};
