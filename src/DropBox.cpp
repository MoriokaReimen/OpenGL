#include <GL/freeglut.h>
#include "arrow.hpp"

using namespace std;

const int WIDTH = 3 * 320;
const int HEIGHT = 3* 240;

#define ODE_MAX_CONTACTS 1024

//ライトの位置
GLfloat lightpos[] = { 0.0, 100.0, 0.0, 0.0 };
const GLfloat FOV = 60.0f;


//シーンの描画
void DrawScene(void)
{
    static const GLfloat spec[] = { 0.3f, 0.3f, 0.3f, 1.0f };    //鏡面反射色
    static const GLfloat ambi[] = { 0.1f, 0.1f, 0.1f, 1.0f };    //環境光
    GLfloat floor_color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    GLfloat blue[] = { 0.4f, 0.4f, 1.0f, 1.0f };
    GLfloat green[] = { 0.4f, 1.0f, 0.4f, 1.0f };
    GLfloat red[] = { 1.0f, 0.4f, 0.4f, 1.0f };

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

    // 床を描画
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  floor_color);
    glPushMatrix();
    glNormal3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 0.0, -100.0);
    glVertex3f(-100.0, 0.0,  100.0);
    glVertex3f( 100.0, 0.0,  100.0);
    glVertex3f( 100.0, 0.0, -100.0);
    glEnd();
    glPopMatrix();

    //drawAxes(5);

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  blue);
    glTranslatef(8, 2, -3);
    glutSolidSphere(3, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  red);
    glTranslatef(-8, 2, 0);
    glutSolidSphere(3, 30, 30);
    glPopMatrix();

    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  red);
    glTranslatef(0, 0, 0);
    glutWireTeapot(5.0);
    glPopMatrix();


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
