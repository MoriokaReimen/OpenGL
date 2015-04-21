#pragma once

#include <memory>
#include <exception>
#include <btBulletDynamicsCommon.h>
#include "ObjectUtil.hpp"

class BaseBulletObject
{
protected:
  btCollisionShape* shape_;
  btScalar mass_{1};
  btVector3 inertia_{0.f, 0.f, 0.f};
  btDefaultMotionState* motion_state_;
  btRigidBody::btRigidBodyConstructionInfo construction_info_;
  btRigidBody* rigid_body_;
  Point xyz_;
  Quaternion quat_;

public:
  virtual void setPosition(const double& x, const double& y, const double& z)
  {
    this->xyz_.set(x, y, z);
    return;
  }

  virtual void setPosition(const Point& point)
  {
    this->xyz_ = point;
    return;
  }
  virtual void setAttitude(const Quaternion& quat)
  {
    this->quat_ = quat;
    return;
  }

  virtual void init()
  {
    this->shape_->calculateLocalInertia(this->mass_,this->inertia_);
    this->motion_state_ =
      new btDefaultMotionState(btTransform(
            btQuaternion(this->quat_.w, this->quat_.x, this->quat_.y, this->quat_.z),
            btVector3(this->xyz_.x, this->xyz_.y, this->xyz_.z)));

   new(&this->construction_info_) btRigidBody::btRigidBodyConstructionInfo(
       this->mass_, this->motion_state_,
       this->shape_,this->inertia_);
   this->rigid_body_= new btRigidBody(this->construction_info_);
   return;
  }

  void setMass(double mass)
  {
    this->mass_ = mass;
    return;
  }

  btRigidBody* getRigidBody()
  {
    if(!this->rigid_body_) throw std::runtime_error("rigid body not initialized");
    return this->rigid_body_;
  }

  void destroy()
  {
      delete rigid_body_->getMotionState();
      delete rigid_body_;
      delete this->shape_;
      return;
  }

  Point getPoint()
  {
    btTransform trans;
    btVector3 buff;
    this->rigid_body_->getMotionState()->getWorldTransform(trans);
    buff = trans.getOrigin();
    Point xyz(buff.x(), buff.y(), buff.z());
    return xyz;
  }

  Quaternion getQuat()
  {
    btTransform trans;
    btQuaternion buff;
    this->rigid_body_->getMotionState()->getWorldTransform(trans);
    buff = trans.getRotation();
    Quaternion quat(buff.w(), buff.x(), buff.y(), buff.z());
    return quat;
  }
};

class BaseBulletSphere : public BaseBulletObject
{

protected:
  GLfloat radius_{10};
public:
  void init(double radius)
  {
    this->radius_ = radius;
    this->shape_ = new btSphereShape(this->radius_);

    BaseBulletObject::init();
    return;
  }

  void init() override
  {
    this->shape_ = new btSphereShape(this->radius_);

    BaseBulletObject::init();
    return;
  }
};

typedef std::shared_ptr<BaseBulletObject> pBaseBulletObject;
typedef std::shared_ptr<BaseBulletSphere> pBaseBulletSphere;
