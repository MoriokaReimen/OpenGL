#include "Object.hpp"
#include <list>
#include <iostream>


using namespace std;


#define ODE_MAX_CONTACTS 1024


class GL
{
    int width  = 3 * 320;
    int height = 3* 240;

    static list<Object*> object_list;
public:
    void init(int argc, char *argv[])
    {
        /* Make Window */
        glutInit(&argc, argv);
        glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
        glutInitWindowPosition(100, 100);
        glutInitWindowSize(this->width, this->height);
        glutCreateWindow("Hello ODE World!!");
        glutDisplayFunc(GL::display);
        glutIdleFunc(GL::idle);

        /* Set Background Color and Depth Buffer */
        glClearColor(1.0, 1.0, 1.0, 1.0);
        glClearDepth(1.0);
        glEnable(GL_DEPTH_TEST);
    }

    void setLight()
    {
        const GLfloat lightpos[] = { 0.0, 100.0, 0.0, 0.0 };
        glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
        glEnable(GL_LIGHT0);
        glEnable(GL_LIGHTING);
        glEnable(GL_NORMALIZE);
    }

    void setCamera()
    {
        //視点の設定
        glViewport(0, 0, this->width, this->height);

        glMatrixMode(GL_PROJECTION);
        glLoadIdentity();
        gluPerspective(60.f, (float)this->width/(float)this->height, 0.1f, 100.0f);

        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        gluLookAt(0.0,20,-50, //カメラの座標
                  0.0,0.0,0.0, // 注視点の座標
                  0.0,1.0,0.0); // 画面の上方向を指すベクトル
    }

    static void display()
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        GL::DrawScene();
        glutSwapBuffers();
    }

    static void idle()
    {
        glutPostRedisplay();
    }

    void run()
    {
        glutMainLoop();
    }

    static void DrawScene(void)
    {
      for(auto it = GL::object_list.begin(); it != GL::object_list.end(); ++it)
      {
        (*it) -> draw();
      }
      return;
    }

    void pushObject(Object* object)
    {
      GL::object_list.push_back(object);
      return;
    }
};

list<Object*> GL::object_list;


int main(int argc, char *argv[])
{
    ObjectColor red(1.0, 0.0, 0.0);
    ObjectColor white(1.f, 1.f, 1.f);
    ObjectColor gray(0.5, 0.5, 0.5);

    Sphere* sphere = new Sphere;
    Floor*  floor  = new Floor;
    Axis*   axis   = new Axis;
    sphere -> setColor(red);
    sphere -> setPosition(0, 10, 0);
    floor  -> setColor(gray);
    GL gl;
    gl.pushObject(floor);
    gl.pushObject(sphere);
    gl.pushObject(axis);
    gl.init(argc, argv);
    gl.setCamera();
    gl.setLight();
    gl.run();
    delete sphere;
    delete floor;
    delete axis;

    return 0;
}
