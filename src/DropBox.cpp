#include "GL.hpp"
#include "Object.hpp"

int main(int argc, char *argv[])
{
    ObjectColor red(1.0, 0.0, 0.0);
    ObjectColor white(1.f, 1.f, 1.f);
    ObjectColor gray(0.5, 0.5, 0.5);

    pSphere sphere(new Sphere);
    pFloor  floor(new Floor);
    pAxis   axis (new Axis);
    sphere -> setColor(red);
    sphere -> setPosition(0, 10, 0);
    floor  -> setColor(gray);
    GL gl(argc, argv);
    gl.pushObject(floor);
    gl.pushObject(sphere);
    gl.pushObject(axis);
    gl.setCamera();
    gl.setLight();
    gl.run();

    return 0;
}
