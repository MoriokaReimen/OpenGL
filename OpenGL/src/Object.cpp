#include "Object.hpp"

Object::~Object()
{
    delete this->bullet_;
    delete this->gl_;
    return;
}

void Object::setPosition(const Math3D::Vector3& xyz)
{
    this->gl_->setPosition(xyz);
    this->bullet_->setPosition(xyz);
    return;
}

void Object::setAttitude(const Math3D::Quaternion& quat)
{
    this->gl_->setAttitude(quat);
    this->bullet_->setAttitude(quat);
    return;
}

void Object::setColor(const GLfloat& r, const GLfloat& g, const GLfloat& b)
{
     this->gl_->setColor(r, g, b);
     return;
}

Math3D::Vector3  Object::getPosition()
{
    return this->bullet_->getPosition();
}

Math3D::Quaternion  Object::getAttitude()
{
    return this->bullet_->getAttitude();
}

void Object::update()
{
     auto pos = this->bullet_->getPosition();
     auto quat = this->bullet_->getAttitude();
     this->gl_->setPosition(pos);
     this->gl_->setAttitude(quat);
     return;
}

Sphere::Sphere(const double& mass, const double& radius)
{
    this->gl_ = new(GLSphere);
    static_cast<GLSphere*>(this->gl_)->setSize(radius);
    this->bullet_ = new(BulletSphere)(mass, radius);
    return;
}

Plane::Plane()
{
    this->gl_ = new(GLPlane)();
    static_cast<GLPlane*>(this->gl_)->setSize(100, 100);
    this->bullet_ = new(BulletPlane)();
    return;
}
