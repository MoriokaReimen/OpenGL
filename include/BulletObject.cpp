#pragma once

#include <btBulletDynamicsCommon.h>
#include "Object.hpp"

class BulletObject : public Object
{
  btCollisionShape* shape_;
  btScalar mass_{1};
  btVector3 inertia_(0, 0, 0);
  btDefaultMotionState* motion_state_;
  btRigidBody::btRigidBodyConstructionInfo construction_info_;
  btRigidBody* rigid_body_

public:
  virtual init()
  virtual void setMass(double mass)
  {
    this->mass_ = mass;
    return;
  }

  virtual void setPosition()
  {
  }

  virtual void setAttitude()
  {
  }

  virtual btRigidBody* getRigidBody()
  {
    return this->rigid_body_;
  }

  virtual void destroyInstance()
  {
      delete rigid_body->getMotionState();
      delete rigid_body;
      delete this->shape;
      return;
  }
};
