#include "DrawObject.hpp"

void drawFloor()
{
    GLfloat floor_color[] = { 0.8f, 0.8f, 0.8f, 1.0f };
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
}

void drawSphere()
{
    GLfloat red[] = { 1.0f, 0.4f, 0.4f, 1.0f };
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  red);
    glTranslatef(-8, 2, 0);
    glutSolidSphere(3, 30, 30);
    glPopMatrix();
}

void drawCube()
{
    GLfloat red[] = { 1.0f, 0.4f, 0.4f, 1.0f };
    glPushMatrix();
    glMaterialfv(GL_FRONT, GL_DIFFUSE,  red);
    glTranslatef(-8, 2, 0);
    glutSolidCube(3);
    glPopMatrix();
}
