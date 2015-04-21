#pragma once

#include <memory>
#include <exception>
#include <btBulletDynamicsCommon.h>
#include "ObjectUtil.hpp"




class BaseBulletObject
{
  btRigidBody* body_;
  btCollisionShape* shape_;
public:
  BaseBulletObject(btRigidBody* body, btCollisionShape* shape)
    : body_(body), shape_(shape)
  {
    return;
  }

  ~BaseBulletObject()
  {
      delete body_->getMotionState();
      delete body_;
      delete this->shape_;
      return;
  }

  Point getPoint()
  {
    btTransform trans;
    btVector3 buff;
    this->body_->getMotionState()->getWorldTransform(trans);
    buff = trans.getOrigin();
    Point xyz(buff.x(), buff.y(), buff.z());
    return xyz;
  }

  Quaternion getQuat()
  {
    btTransform trans;
    btQuaternion buff;
    this->body_->getMotionState()->getWorldTransform(trans);
    buff = trans.getRotation();
    Quaternion quat(buff.w(), buff.x(), buff.y(), buff.z());
    return quat;
  }

  btRigidBody* getBody()
  {
    return this->body_;
  }
};
typedef std::shared_ptr<BaseBulletObject> pBaseBulletObject;

class BaseBulletSphereFactory
{

public:
  double radius;
  btScalar mass;
  Point xyz;
  Quaternion quat;

  pBaseBulletObject spawn()
  {
    btVector3 inertia{0.f, 0.f, 0.f};
    btCollisionShape* shape = new btSphereShape(radius);
    shape->calculateLocalInertia(mass, inertia);

    btDefaultMotionState* motion_state =
        new btDefaultMotionState(btTransform(
              btQuaternion(quat.w, quat.x, quat.y, quat.z),
              btVector3(xyz.x, xyz.y, xyz.z)));

    btRigidBody::btRigidBodyConstructionInfo construction_info(
         mass, motion_state,
         shape,       inertia);

    btRigidBody* body = new btRigidBody(construction_info);
    pBaseBulletObject sphere(new BaseBulletObject(body, shape));
   return sphere;
  }
};
/*
double BaseBulletSphereFactory::radius{10};
btScalar BaseBulletSphereFactory::mass{1};
Point BaseBulletSphereFactory::xyz{0, 0, 0};
Quaternion BaseBulletSphereFactory::quat{1, 0, 0, 0};
*/
// pBaseBulletObject BaseBulletSphereFactory::spawn();
// */
