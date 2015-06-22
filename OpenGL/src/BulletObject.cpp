#include "BulletObject.hpp"

BulletObject::~BulletObject()
{
    delete body_->getMotionState();
    delete body_;
    delete this->shape_;
    return;
}

Math3D::Vector3 BulletObject::getPosition()
{
  btTransform trans;
  btVector3 buff;
  this->body_->getMotionState()->getWorldTransform(trans);
  buff = trans.getOrigin();
  Math3D::Vector3 xyz(buff.x(), buff.y(), buff.z());
  return xyz;
}

Math3D::Quaternion BulletObject::getAttitude()
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

void BulletObject::setPosition(const Math3D::Vector3& pos)
{
    btTransform transform;
    btVector3 position(pos.x, pos.y, pos.z);
    this->body_->getMotionState()->getWorldTransform(transform);
    transform.setOrigin(position);
    this->body_->getMotionState()->setWorldTransform(transform);
    this->body_->setCenterOfMassTransform(transform);
    return;
}

void BulletObject::setAttitude(const Math3D::Quaternion& quat)
{
    btTransform transform;
    btQuaternion rotation(quat.x, quat.y, quat.z, quat.w);
    this->body_->getMotionState()->getWorldTransform(transform);
    transform.setRotation(rotation);
    this->body_->getMotionState()->setWorldTransform(transform);
    this->body_->setCenterOfMassTransform(transform);
    return;
}

BulletSphere::BulletSphere(const double& mass, const double& radius)
{
  btVector3 inertia{0.f, 0.f, 0.f};
  this->shape_ = new btSphereShape(radius);
  this->shape_->calculateLocalInertia(mass, inertia);

  btDefaultMotionState* motion_state =
      new btDefaultMotionState(btTransform(
            btQuaternion(0, 0, 0),
            btVector3(0, 1, 0)));

  btRigidBody::btRigidBodyConstructionInfo construction_info(
       mass, motion_state,
       this->shape_,       inertia);


  this->body_ = new btRigidBody(construction_info);
    if(mass==0.0)
    {
    this->body_->setCollisionFlags(this->body_->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
    this->body_->setActivationState(DISABLE_DEACTIVATION);
    }
  return;
}

BulletPlane::BulletPlane()
{
    this->shape_ = new btStaticPlaneShape(btVector3(0, 0, 1), 1);
    btDefaultMotionState* groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0), btVector3(0, 0, 1)));
    btRigidBody::btRigidBodyConstructionInfo
    groundRigidBodyCI(0, groundMotionState, this->shape_, btVector3(0, 0, 0));
    this->body_ = new btRigidBody(groundRigidBodyCI);
    return;
}

BulletBox::BulletBox(const double& mass, const double& a, const double& b, const double c)
{
  btVector3 inertia{0.f, 0.f, 0.f};
  this->shape_ = new btBoxShape(btVector3(a,b,c));
  this->shape_->calculateLocalInertia(mass, inertia);

  btDefaultMotionState* motion_state =
      new btDefaultMotionState(btTransform(
            btQuaternion(0, 0, 0),
            btVector3(0, 1, 0)));

  btRigidBody::btRigidBodyConstructionInfo construction_info(
       mass, motion_state,
       this->shape_,       inertia);


  this->body_ = new btRigidBody(construction_info);
  if(mass==0.0)
  {
       this->body_->setCollisionFlags(this->body_->getCollisionFlags() | btCollisionObject::CF_KINEMATIC_OBJECT);
       this->body_->setActivationState(DISABLE_DEACTIVATION);
  }
  return;
}
