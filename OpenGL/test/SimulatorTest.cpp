#include <cstdlib>
#include "World.hpp"
#include "Object.hpp"

int main()
{
    Math3D::Vector3 red_h(10, 100, 0), green_h(-10, 120, 0), blue_h(0, 140, 10), zero(0, 0, 0);
    Math3D::Quaternion quat(0, 0, 0, 1), slope;
    Math3D::Degree degree[3];
    degree[0] = 0;
    degree[1] = 0;
    degree[2] = 30;
    slope.fromRPY(degree[0], degree[1], degree[2]);
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

    Box* ground = new Box(0, 15, 10, 10);
    ground->setColor(0.3, 0.3, 0.3);
    ground->setAttitude(slope);



    world.pushObject(red);
    world.pushObject(green);
    world.pushObject(blue);

    world.pushObject(ground);

    world.setLight();
    world.run();

    return EXIT_SUCCESS;
}
