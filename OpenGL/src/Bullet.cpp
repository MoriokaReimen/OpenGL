#include "Bullet.hpp"

constexpr double TIME_STEP = 1/ 1000.f;
constexpr double GRAVITY = 9.8;
Bullet::Bullet()
{
  this->broadphase_ = new btDbvtBroadphase();
  this->collision_config_ = new btDefaultCollisionConfiguration();
  this->dispatcher_ = new btCollisionDispatcher(this->collision_config_);
  this->solver_ = new btSequentialImpulseConstraintSolver;
  this->world_ = new btDiscreteDynamicsWorld(this->dispatcher_, this->broadphase_, this->solver_, this->collision_config_);

  this->world_->setGravity(btVector3(0, - GRAVITY, 0));

  return;
}


Bullet::~Bullet()
{
  delete this->world_;
  delete this->solver_;
  delete this->collision_config_;
  delete this->dispatcher_;
  delete this->broadphase_;

  return;
}

void Bullet::step()
{
    this->time += TIME_STEP;
    this->world_->stepSimulation(TIME_STEP, 10);
    return;
}

void Bullet::pushObject(BulletObject* object)
{
  this->world_->addRigidBody(object->getBody());
  this->object_list_.push_back(object);
  return;
}
