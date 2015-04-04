#include "GL/glut.h"

//ライトの位置
GLfloat lightpos[] = { 2.0, 4.0, 1.0, 0.0 };
const GLfloat FOV = 45.0f;

//シーンの描画
void display(void)
{
    // show Tea Pot
    glPushMatrix();
    GLfloat teapot_color[4] = { 0.8f, 0.f, 0.f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  teapot_color);
    glutSolidTeapot(0.5);
    glPopMatrix();

    // 床を描画
    glPushMatrix();
    GLfloat floor_color[4] = { 0.8f, 0.f, 0.f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  floor_color);
    glNormal3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-10.0, 0.0, -10.0);
    glVertex3f(-10.0, 0.0,  10.0);
    glVertex3f( 10.0, 0.0,  10.0);
    glVertex3f( 10.0, 0.0, -10.0);
    glEnd();
    glPopMatrix();

    glutSwapBuffers();
}

void idle()
{
  glutPostRedisplay();
  //Sleep(1);
}


void Init(void)
{
    glViewport(0,0,640,480);
    // 背景色
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glShadeModel(GL_FLAT);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(FOV, (float)640/(float)480, 0.01f, 20.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glPushMatrix();

    //視点の設定
    gluLookAt(1.0,0.5,1.0, //カメラの座標
              0.0,0.0,0.0, // 注視点の座標
              0.0,1.0,0.0); // 画面の上方向を指すベクトル

    // 光源位置
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);

    glPopMatrix();
}

int main(int argc, char* argv[])
{
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(640, 480);
	glutCreateWindow("Solid Teapot");
	glutIdleFunc(idle);
	glutDisplayFunc(display);
  Init();
	glutMainLoop();

	return 0;
}
