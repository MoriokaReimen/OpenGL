#include "BaseBullet.hpp"

BaseBullet::BaseBullet()
{
  this->broadphase_ = new btDbvtBroadphase();
  this->collision_config_ = new btDefaultCollisionConfiguration();
  this->dispatcher_ = new btCollisionDispatcher(this->collision_config_);
  this->solver_ = new btSequentialImpulseConstraintSolver;
  this->world_ = new btDiscreteDynamicsWorld(this->dispatcher_, this->broadphase_, this->solver_, this->collision_config_);

  this->world_->setGravity(btVector3(0, 0, - this->gravity_));

  return;
}


BaseBullet::~BaseBullet()
{
  for(auto it = this->object_list_.begin(); it != this->object_list_.end(); ++it)
  {
    this->world_->removeRigidBody((*it)->getRigidBody());
    (*it)->destroy();
  }
  delete this->world_;
  delete this->solver_;
  delete this->collision_config_;
  delete this->dispatcher_;
  delete this->broadphase_;

  return;
}

void BaseBullet::step()
{
    this->world_->stepSimulation(1/ 60.f, 10);
    return;
}

void BaseBullet::pushObject(pBaseBulletObject object)
{
  this->world_->addRigidBody(object->getRigidBody());
  this->object_list_.push_back(object);
  return;
}
