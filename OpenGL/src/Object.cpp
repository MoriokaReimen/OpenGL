#include "Object.hpp"

class Object
{
public:
    GLObject* gl_;
    BulletObject* bullet_;

    virtual ~Object()
    {
        delete this->bullet_;
        delete this->gl_;
        return;
    }

    void setPosition(const Math3D::Vector3& xyz)
    {
        this->gl_->setPosition(xyz);
        this->bullet_->setPosition(xyz);
        return;
    }

    void setAttitude(const Math3D::Quaternion& quat);
    {
        this->gl_->setAttitude(quat);
        this->bullet_->setAttitude(quat);
        return;
    }

    virtual void setColor(const GLfloat& r, const GLfloat& g, const GLfloat& b)
    {
         this->gl_->setColor(r, g, b);
         return;
    }

    virtual Math3D::Vector3  getPosition()
    {
        return this->bullet_->getPosition();
    }

    virtual Math3D::Quaternion  getAttitude()
    {
        return this->bullet_->getAttitude();
    }

    virtual void update()
    {
         auto pos = this->bullet_->getPosition();
         auto quat = this->bullet_getAttitude();
         this->gl_->setPosition(pos);
         this->gl_->setAttitude(quat);
         return;
    }
};

class Sphere : public Object
{
public:
    Sphere(Math3D::Vector3 position, Math3D::Quaternion quat, const double& mass, const double& radius)
    {
        this->gl_ = new GLSphere();
        this->bullet_ = new BulletSphere();
        return;
    }
};
