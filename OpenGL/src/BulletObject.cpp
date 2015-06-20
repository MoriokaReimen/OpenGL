#include "BulletObject.hpp"

BulletObject::~BulletObject()
{
    delete body_->getMotionState();
    delete body_;
    delete this->shape_;
    return;
}

Math3D::Vector3 BulletObject::getPoint()
{
  btTransform trans;
  btVector3 buff;
  this->body_->getMotionState()->getWorldTransform(trans);
  buff = trans.getOrigin();
  Math3D::Vector3 xyz(buff.x(), buff.y(), buff.z());
  return xyz;
}

Math3D::Quaternion BulletObject::getQuat()
{
  btTransform trans;
  btQuaternion buff;
  this->body_->getMotionState()->getWorldTransform(trans);
  buff = trans.getRotation();
  Math3D::Quaternion quat(buff.w(), buff.x(), buff.y(), buff.z());
  return quat;
}

btRigidBody* BulletObject::getBody()
{
  return this->body_;
}

void BulletObject::setPosition(Math3D::Vector3 pos)
{
    btTransform transform;
    btVector3 position(pos.x, pos.y, pos.z);
    this->body_->getMotionState()->getWorldTransform(transform);
    transform.setOrigin(position);
    this->body_->setCenterOfMassTransform(transform);
    return;
}

void BulletObject::setAttitude(Math3D::Quaternion quat)
{
    btTransform transform;
    btQuaternion rotation(quat.w, quat.x, quat.y, quat.z);
    this->body_->getMotionState()->getWorldTransform(transform);
    transform.setRotation(rotation);
    this->body_->getMotionState()->setWorldTransform(transform);
    return;
}

BulletSphere::BulletSphere(Math3D::Vector3 xyz, Math3D::Quaternion quat, double mass, double radius)
{
  btVector3 inertia{0.f, 0.f, 0.f};
  this->shape_ = new btSphereShape(radius);
  this->shape_->calculateLocalInertia(mass, inertia);

  btDefaultMotionState* motion_state =
      new btDefaultMotionState(btTransform(
            btQuaternion(quat.w, quat.x, quat.y, quat.z),
            btVector3(xyz.x, xyz.y, xyz.z)));

  btRigidBody::btRigidBodyConstructionInfo construction_info(
       mass, motion_state,
       this->shape_,       inertia);

  this->body_ = new btRigidBody(construction_info);
  return;
}

BulletPlane::BulletPlane(Math3D::Vector3 xyz, Math3D::Quaternion quat)
{
  btVector3 inertia{0.f, 0.f, 0.f};
  this->shape_ = new btStaticPlaneShape(btVector3(0, 0, 1), 0);

  btDefaultMotionState* motion_state =
      new btDefaultMotionState(btTransform(
            btQuaternion(quat.w, quat.x, quat.y, quat.z),
            btVector3(xyz.x, xyz.y, xyz.z)));

  btRigidBody::btRigidBodyConstructionInfo construction_info(
       10, motion_state,
       this->shape_,       inertia);

  this->body_ = new btRigidBody(construction_info);
  return;
}
