#include <cstdlib>
#include "World.hpp"
#include "Object.hpp"

int main()
{
    Math3D::Vector3 red_h(0, 0, 50), green_h(0, 10, 50), blue_h(10, 0, 50), zero(0, 0, 0);
    Math3D::Quaternion quat(0, 0, 0, 1);
    World world;
    world.setCamera();

    Sphere* red = new Sphere(10.0, 1.0);
    Sphere* green = new Sphere(10.0, 1.0);
    Sphere* blue = new Sphere(10.0, 1.0);

    red->setColor(1, 0, 0);
    red->setPosition(red_h);

    green->setColor(0, 1, 0);
    green->setPosition(green_h);

    blue->setColor(0, 0, 1);
    blue->setPosition(blue_h);

    Plane* plane = new Plane();
    plane->setColor(0.3, 0.3, 0.3);
    plane->setPosition(zero);

    world.pushObject(red);
    world.pushObject(green);
    world.pushObject(blue);

    world.pushObject(plane);

    world.setLight();
    world.run();

    delete plane;
    delete red;
    delete green;
    delete blue;

    return EXIT_SUCCESS;
}
