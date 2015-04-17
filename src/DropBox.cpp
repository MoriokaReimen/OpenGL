#include "GL.hpp"
#include "Object.hpp"

int main(int argc, char *argv[])
{
    GL gl(argc, argv);
    ObjectColor red(1.0, 0.0, 0.0);
    ObjectColor blue(0.0, 1.0, 0.0);
    ObjectColor white(1.f, 1.f, 1.f);
    ObjectColor gray(0.5, 0.5, 0.5);
    Quaternion quat;
    quat.fromAngleAxis(120, 0.f, 0.f, 1.f);
    Texture texture("./resource/toyoura.jpg");

    pCube     cube(new Cube);
    pSphere   sphere(new Sphere);
    pFloor    floor(new Floor);
    pAxis     axis(new Axis);
    pCylinder cylinder(new Cylinder);

    cube-> setSize(5, 5, 5);
    cube-> setPosition(30, 0, 0);

    sphere -> setColor(red);
    sphere -> setPosition(0, 10, 0);
    sphere -> setAttitude(quat);
    sphere -> setSize(10);

    floor  -> setTexture(texture);
    floor  -> setAttitude(quat);
    floor  -> setSize(100.f, 100.f);

    cylinder -> setColor(blue);
    cylinder -> setAttitude(quat);
    cylinder -> setAttitude(quat);
    cylinder -> setSize(5, 10);

    gl.pushObject(floor);
    gl.pushObject(sphere);
    gl.pushObject(axis);
    gl.pushObject(cylinder);
    gl.pushObject(cube);
    gl.setCamera();
    gl.setLight();
    gl.run();

    return 0;
}
