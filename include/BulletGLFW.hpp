#pragma once
#include "GLFW.hpp"
#include <btBulletDynamicsCommon.h>

class BulletGLFW : public GLFW
{
  btBroadphaseInterface* broadphase;
  btDefaultCollisionConfiguration* collisionConfiguration;
  btCollisionDispatcher* dispatcher;
  btSequentialImpulseConstraintSolver* solver;
  btDiscreteDynamicsWorld* dynamicsWorld;
  double gravity{9.80665};
public:
  BulletGLFW();
  ~BulletGLFW();
  virtual void run() override;
};
