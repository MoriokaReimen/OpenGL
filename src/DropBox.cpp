// #include "arrow.hpp"
#include "Object.hpp"

using namespace std;

const int WIDTH = 3 * 320;
const int HEIGHT = 3* 240;

#define ODE_MAX_CONTACTS 1024

//ライトの位置
GLfloat lightpos[] = { 0.0, 100.0, 0.0, 0.0 };
const GLfloat FOV = 60.0f;

Sphere sphere;
ObjectColor red(1.0, 0.0, 0.0);
ObjectColor gray(0.8, 0.8, 0.8);
Floor floor;


//シーンの描画
void DrawScene(void)
{
    static const GLfloat spec[] = { 0.3f, 0.3f, 0.3f, 1.0f };    //鏡面反射色
    static const GLfloat ambi[] = { 0.1f, 0.1f, 0.1f, 1.0f };    //環境光

    glEnable(GL_LIGHTING);
    glEnable(GL_DEPTH_TEST);
    glCullFace(GL_BACK);
    glEnable(GL_CULL_FACE);
    glDisable(GL_COLOR_MATERIAL);

    // 材質を設定
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_AMBIENT,  ambi);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);

    glPolygonMode(GL_FRONT, GL_FILL);

    floor.draw();
    sphere.draw();



    //drawAxes(5);

}


void display(void)
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glViewport(0, 0, WIDTH, HEIGHT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, (float)WIDTH/(float)HEIGHT, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    //視点の設定
    gluLookAt(0.0,10,20, //カメラの座標
              0.0,0.0,0.0, // 注視点の座標
              0.0,1.0,0.0); // 画面の上方向を指すベクトル

    // 光源位置
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    DrawScene();

    glPopMatrix();

    glutSwapBuffers();
}


void idle(void)
{
    glutPostRedisplay();
    //Sleep(1);
}

void Init(void)
{
    // 背景色
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0);
    glEnable(GL_NORMALIZE);
}

int main(int argc, char *argv[])
{
    sphere.setColor(red);
    sphere.setPosition(0, 0, 0);
    floor.setColor(gray);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(WIDTH, HEIGHT);
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE);
    glutCreateWindow("Hello ODE World!!");
    glutDisplayFunc(display);
    glutIdleFunc(idle);
    Init();
    glutMainLoop();
    return 0;
}
