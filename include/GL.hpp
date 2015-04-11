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
    int width;
    int height;
    static void display();
    static void DrawScene(void);
    static void idle();

    static std::list<pObject> object_list;
public:
    GL(int argc, char** argv, int bwidth = 960, int bheight = 720);
    void setLight(GLfloat x = 0.f, GLfloat y = 100.f, GLfloat z = -50.f);
    void setLight(const Point& xyz);
    void setCamera();
    void setCamera(const Point& camera_pos, const Point& look_at);
    void run();
    void pushObject(pObject object);
};

