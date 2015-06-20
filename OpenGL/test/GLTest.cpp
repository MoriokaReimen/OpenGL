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
    Math3D::Quaternion quat;
    Math3D::Degree angle(120);
    Math3D::Vector3 pos(0, 0, 1);
    quat.fromAngleAxis(angle, pos);
    GLTexture texture(toyoura);
    GLSphere*   sphere = new GLSphere();
    GLPlane*   floor = new GLPlane();
    sphere -> setColor(red);
    sphere -> setSize(10);
    floor  -> setTexture(texture);
    floor  -> setAttitude(quat);
    floor  -> setSize(100.f, 100.f);
    gl.pushObject(sphere);
    gl.pushObject(floor);
    gl.setCamera();
    gl.setLight();
    gl.run();

    delete sphere;
    delete sphere;

    return 0;
}
