#include <cstdlib>
#include "World.hpp"
#include "Object.hpp"

int main()
{
    Math3D::Vector3 h(0, 0, 1000), zero(0, 0, 0);
    Math3D::Quaternion quat(0, 0, 0, 1);
    World world;
    world.setCamera();
    Sphere* sphere = new Sphere(10.0, 2.0);
    sphere->setPosition(zero);
    sphere->setColor(0, 0, 1);
    Plane* plane = new Plane();
    plane->setColor(0.3, 0.3, 0.3);
    plane->setPosition(zero);
    world.pushObject(sphere);
    world.pushObject(plane);
    world.setLight();
    world.run();

    return EXIT_SUCCESS;
}
