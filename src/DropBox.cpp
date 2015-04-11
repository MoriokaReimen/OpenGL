#include "Object.hpp"

using namespace std;


#define ODE_MAX_CONTACTS 1024

Sphere sphere;
ObjectColor red(1.0, 0.0, 0.0);
ObjectColor gray(0.8, 0.8, 0.8);
Floor floor;
Axis axis;

class GL
{
    int width  = 3 * 320;
    int height = 3* 240;

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
        gluLookAt(0.0,10,20, //カメラの座標
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
        floor.draw();
        sphere.draw();
        axis.draw();
    }
};


int main(int argc, char *argv[])
{
    GL gl;
    sphere.setColor(red);
    sphere.setPosition(0, 0, 0);
    floor.setColor(gray);
    gl.init(argc, argv);
    gl.setCamera();
    gl.setLight();
    gl.run();

    return 0;
}
