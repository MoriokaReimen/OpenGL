#include "BulletGLFW.hpp"
BulletGLFW::BulletGLFW()
  : GLFW()
{
  this->broadphase_ = new btDbvtBroadphase();
  this->collision_config_ = new btDefaultCollisionConfiguration();
  this->dispatcher_ = new btCollisionDispatcher(this->collision_config_);
  this->solver_ = new btSequentialImpulseConstraintSolver;
  this->world_ = new btDiscreteDynamicsWorld(this->dispatcher_, this->broadphase_, this->solver_, this->collision_config_);

  this->world_->setGravity(btVector3(0, 0, - this->gravity_));

  return;
}

BulletGLFW::~BulletGLFW()
{
  delete this->world_;
  delete this->solver_;
  delete this->collision_config_;
  delete this->dispatcher_;
  delete this->broadphase_;

  return;
}

void BulletGLFW::run()
{
  do {
    this->world_->stepSimulation(1/ 60.f, 10);
    this->display();
  } while(!glfwWindowShouldClose(this->window_));
}
