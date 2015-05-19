#include "GL.hpp"
#include "GLObject.hpp"

int main(int argc, char *argv[])
{
    GL gl;
    ToyouraPNG toyoura;
    ObjectColor red(1.0, 0.0, 0.0);
    ObjectColor blue(0.0, 1.0, 0.0);
    ObjectColor white(1.f, 1.f, 1.f);
    ObjectColor gray(0.5, 0.5, 0.5);
    Quaternion quat;
    quat.fromAngleAxis(120, 0.f, 0.f, 1.f);
    GLTexture texture(toyoura);
    pGLSphere   sphere(new GLSphere);
    pGLFloor   floor(new GLFloor);
    sphere -> setColor(red);
    sphere -> setSize(10);
    floor  -> setTexture(texture);
    floor  -> setAttitude(quat);
    floor  -> setSize(100.f, 100.f);
/*
    pCube     cube(new Cube);
    pSphere   sphere(new Sphere);
    pFloor    floor(new Floor);
    pAxis     axis(new Axis);
    pCylinder cylinder(new Cylinder);

    cube-> setSize(5, 5, 5);
    cube-> setPosition(30, 0, 0);

    sphere -> setPosition(0, 10, 0);
    sphere -> setAttitude(quat);


    cylinder -> setColor(blue);
    cylinder -> setAttitude(quat);
    cylinder -> setAttitude(quat);
    cylinder -> setSize(5, 10);

    glfw.pushObject(floor);
    glfw.pushObject(axis);
    glfw.pushObject(cylinder);
    glfw.pushObject(cube);
*/
    gl.pushObject(sphere);
    gl.pushObject(floor);
    gl.setCamera();
    gl.setLight();
    gl.run();

    return 0;
}
