#pragma once

#include <memory>
#include <exception>
#include <btBulletDynamicsCommon.h>
#include "Object.hpp"

class BulletObject : public Object
{
protected:
  btCollisionShape* shape_;
  btScalar mass_{1};
  btVector3 inertia_{0.f, 0.f, 0.f};
  btDefaultMotionState* motion_state_;
  btRigidBody::btRigidBodyConstructionInfo construction_info_;
  btRigidBody* rigid_body_;

public:
  /*
  BulletObject()
  {
    Object::Object();
    this->shape_->calculateLocalInertia(this->mass_,this->inertia_);
    return;
  }
  */

  virtual void init()
  {
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

  virtual void setMass(double mass)
  {
    this->mass_ = mass;
    this->shape_->calculateLocalInertia(this->mass_,this->inertia_);
    return;
  }

  virtual btRigidBody* getRigidBody()
  {
    if(!this->rigid_body_) throw std::runtime_error("rigid body not initialized");
    return this->rigid_body_;
  }

  virtual void destroy()
  {
      delete rigid_body_->getMotionState();
      delete rigid_body_;
      delete this->shape_;
      return;
  }
};

class BulletSphere : public BulletObject
{

protected:
  GLfloat radius_{10};
public:
  void draw() override
  {
    btTransform trans;
    this->motion_state_->getWorldTransform(trans);
    btVector3 pos = trans.getOrigin();
    btQuaternion rot = trans.getRotation();
    this->xyz_.set(pos.x(), pos.y(), pos.z());
    this->quat_.set(rot.w(), rot.x(), rot.y(), rot.z());

    GLfloat x, y, z, angle;
    this->quat_.toGLAngleAxis(angle, x, y, z);
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->color_.toArray());
    glTranslatef(this->xyz_.x, this->xyz_.z, this->xyz_.y);
    glRotatef(angle, x, y, z);
    for(int i = 0; i <= 30; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / 30);
        double z0  = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / 30);
        double z1  = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(int j = 0; j <= 30; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / 30;
            double rx = cos(lng);
            double ry = sin(lng);

            glNormal3f(rx * zr0, ry * zr0, z0);
            glVertex3f(this->radius_ * rx * zr0, this->radius_ * ry * zr0, this->radius_ * z0);
            glNormal3f(rx * zr1, ry * zr1, z1);
            glVertex3f(this->radius_ * rx * zr1, this->radius_ * ry * zr1, this->radius_ * z1);
        }
        glEnd();
    }
    glPopMatrix();
    return;
  }
};

typedef std::shared_ptr<BulletObject> pBulletObject;
typedef std::shared_ptr<BulletSphere> pBulletSphere;
