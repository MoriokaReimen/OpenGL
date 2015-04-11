#pragma once
#include "Object.hpp"
#include <GL/freeglut.h>
#include <list>
#include <memory>

typedef std::shared_ptr<Sphere> pSphere;
typedef std::shared_ptr<Object> pObject;
typedef std::shared_ptr<Floor> pFloor;
typedef std::shared_ptr<Axis> pAxis;

class GL
{
    int width{960};
    int height{720};
    static void display();
    static void DrawScene(void);
    static void idle();

    static std::list<pObject> object_list;
public:
    GL(int argc, char** argv);
    void setLight();
    void setCamera();
    void run();
    void pushObject(pObject object);
};

