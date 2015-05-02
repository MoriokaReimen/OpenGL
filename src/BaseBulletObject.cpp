#include "BaseBulletObject.hpp"
btScalar BaseBulletObjectFactory::mass{1};
Point BaseBulletObjectFactory::xyz{0, 0, 0};
Quaternion BaseBulletObjectFactory::quat{1, 0, 0, 0};



BaseBulletObject::BaseBulletObject(btRigidBody* body, btCollisionShape* shape)
  : body_(body), shape_(shape)
{
  return;
}

BaseBulletObject::~BaseBulletObject()
{
    delete body_->getMotionState();
    delete body_;
    delete this->shape_;
    return;
}

Point BaseBulletObject::getPoint()
{
  btTransform trans;
  btVector3 buff;
  this->body_->getMotionState()->getWorldTransform(trans);
  buff = trans.getOrigin();
  Point xyz(buff.x(), buff.y(), buff.z());
  return xyz;
}

Quaternion BaseBulletObject::getQuat()
{
  btTransform trans;
  btQuaternion buff;
  this->body_->getMotionState()->getWorldTransform(trans);
  buff = trans.getRotation();
  Quaternion quat(buff.w(), buff.x(), buff.y(), buff.z());
  return quat;
}

btRigidBody* BaseBulletObject::getBody()
{
  return this->body_;
}

pBaseBulletObject BaseBulletObjectFactory::spawnSphere(double radius)
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

pBaseBulletObject BaseBulletObjectFactory::spawnStaticPlane()
{
  btVector3 inertia{0.f, 0.f, 0.f};
  btCollisionShape* shape = new btStaticPlaneShape(btVector3(0, 0, 1), 0);

  btDefaultMotionState* motion_state =
      new btDefaultMotionState(btTransform(
            btQuaternion(quat.w, quat.x, quat.y, quat.z),
            btVector3(xyz.x, xyz.y, xyz.z)));

  btRigidBody::btRigidBodyConstructionInfo construction_info(
       mass, motion_state,
       shape,       inertia);

  btRigidBody* body = new btRigidBody(construction_info);
  pBaseBulletObject static_plane(new BaseBulletObject(body, shape));
  return static_plane;
}
