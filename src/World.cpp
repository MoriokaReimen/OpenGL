#include "World.hpp"

World::World()
{
    return;
}

World::~World()
{
    return;
}

void World::setLight(GLfloat x, GLfloat y, GLfloat z)
{
    this->gl.setLight(x, y, z);
    return;
}

void World::setLight(const Math3D::Vector3& xyz)
{
    this->gl.setLight(xyz);
    return;
}

void World::setCamera()
{
    this->gl.setCamera();
    return;
}

void World::setCamera(const Math3D::Vector3& camera_pos, const Math3D::Vector3& look_at)
{
    this->gl.setCamera(camera_pos, look_at);
    return;
}

void World::run()
{
    do {
        this->display();
    } while(this->gl.isClose());
}
/*
void World::pushObject(pObject object)
{
    this->gl->pushObject(object->gl_object);
    this->bullet->pushObject(object->bullet_object);
    return;
}
*/

void World::display()
{
    this->gl.display();
    this->bullet.step();
    return;
}
