#include <GL/freeglut.h>
#include <ode/ode.h>
#include <vector>

using namespace std;

#define WIDTH 320
#define HEIGHT 240

#define ODE_MAX_CONTACTS 1024

const GLfloat FOV = 45.0f;

void prepareGL(void)
{
    glViewport(0,0,640,480);

    // 背景色
    glClearColor(0.8,0.8,0.9,0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glDisable(GL_COLOR_MATERIAL);
    glShadeModel(GL_FLAT);

    // Projection
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective (45,1.3333,0.2,20);

    // Initialize ModelView matrix
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Light source
    GLfloat lightpos[] = { 0.0, 0.0, 1.0, 0.0 };
    GLfloat lightdiff[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat lightspec[] = { 1.0, 1.0, 1.0, 1.0 };
    glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, lightdiff);
    glLightfv(GL_LIGHT0, GL_SPECULAR, lightspec);
    glEnable(GL_LIGHT0);

    // View transformation
    gluLookAt (2*2.4, 2*3.6, 2*4.8,
               0.0, 0.0, 0.0,
               0.0, 1.0, 0.0);
    // set up material
    static const GLfloat spec[] = {0.3f, 0.3f, 0.3f, 1.0f};
    static const GLfloat ambi[] = {0.1f, 0.1f, 0.1f, 1.0f};
    glMaterialfv(GL_FRONT, GL_SPECULAR, spec);
    glMaterialfv(GL_FRONT, GL_AMBIENT, ambi);
    glMaterialf(GL_FRONT, GL_SHININESS, 50.0);
}
//シーンの描画
void DrawScene(void)
{
    static GLfloat blue[] = { 0.0f, 0.0f, 1.0f, 1.0f };//青
    GLfloat red[] = { 1.0f, 0.0f, 0.0f, 1.0f };//青
    GLfloat green[] = { 0.0f, 1.0f, 0.0f, 1.0f };//青

    // draw ball
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE, green);
    glTranslated(0,1,0);
    glutSolidSphere(1.0, 30, 30);
    //glPopMatrix();

    // 床を描画
    GLfloat color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  color);
    glPushMatrix();
    glNormal3f(0.0, 1.0, 0.0);
    glBegin(GL_POLYGON);
    glVertex3f(-100.0, 0.0, -100.0);
    glVertex3f(-100.0, 0.0,  100.0);
    glVertex3f( 100.0, 0.0,  100.0);
    glVertex3f( 100.0, 0.0, -100.0);
    glEnd();
    glPopMatrix();

}


void draw(void)
{
  DrawScene();
  glutSwapBuffers();
}


void idle(void)
{
    glutPostRedisplay();
}


int main(int argc, char *argv[])
{
    const int width = 640;
    const int height = 480;

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGB | GLUT_DOUBLE);
    glutInitWindowPosition(100, 100);
    glutInitWindowSize(width, height);
    glutCreateWindow("Hello ODE World!!");
    glutDisplayFunc(draw);
    glutIdleFunc(idle);
    prepareGL();
    glutMainLoop();
    return 0;
}
