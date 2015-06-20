#include "World.hpp"

World::World()
{
    this->gl_ = new GL;
    this->bullet_ = new Bullet;
    return;
}

World::~World()
{
    delete this->gl_;
    delete this->bullet_;
    return;
}

void World::setLight(GLfloat x, GLfloat y, GLfloat z)
{
    this->gl_->setLight(x, y, z);
    return;
}

void World::setLight(const Math3D::Vector3& xyz)
{
    this->gl_->setLight(xyz);
    return;
}

void World::setCamera()
{
    this->gl_->setCamera();
    return;
}

void World::setCamera(const Math3D::Vector3& camera_pos, const Math3D::Vector3& look_at)
{
    this->gl_->setCamera(camera_pos, look_at);
    return;
}

void World::run()
{
    do {
        this->display();
    } while(this->gl->isClose());
}

void World::pushObject(Object* object)
{
    this->gl_->pushObject(object->gl_);
    this->bullet_->pushObject(object->bullet_);
    return;
}

void World::display()
{
    this->gl_->display();
    this->bullet_->step();
    return;
}
