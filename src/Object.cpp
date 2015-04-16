#include "Object.hpp"


void Object::setPosition(double x, double y, double z)
{
    Point buff(x, y, z);
    this->xyz = buff;
    return;
}

void Object::setPosition(Point point)
{
    this->xyz = point;
    return;
}

void Object::setColor(ObjectColor bcolor)
{
    this->color = bcolor;
    return;
}

void Object::setColor(GLfloat br, GLfloat bg, GLfloat bb)
{
    this->color.r = br;
    this->color.g = bg;
    this->color.b = bb;
    return;
}

void Object::setAttitude(const Quaternion& bquat)
{
    this->quat = bquat;
    return;
}

void Object::setTexture(Texture& texture)
{
    this-> texture = texture;
    return;
}

void Sphere::draw() // protect someday
{
    GLfloat x, y, z, angle;
    this->quat.toGLAxisAngle(x, y, z, angle);
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());
    glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
    glRotatef(x, y, z, angle);
    glutSolidSphere(3, 30, 30);
    glPopMatrix();
    return;
}

void Cube::draw() // protect someday
{
    GLfloat x, y, z, angle;
    this->quat.toGLAxisAngle(x, y, z, angle);
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());
    glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
    glRotatef(x, y, z, angle);
    glutSolidCube(3);
    glPopMatrix();
    return;
}

void Floor::draw() // protect someday
{
    GLfloat x, y, z, angle;
    this->quat.toGLAxisAngle(x, y, z, angle);
    if(this->texture.getID()) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texture.getID());
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());
        glPushMatrix();
        glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.f, 0.f);
        glVertex3f(-100.0, 0.0, -100.0);
        glTexCoord2f(0.f, 5.f);
        glVertex3f(-100.0, 0.0,  100.0);
        glTexCoord2f(5.f, 5.f);
        glVertex3f( 100.0, 0.0,  100.0);
        glTexCoord2f(5.f, 0.f);
        glVertex3f( 100.0, 0.0, -100.0);
        glEnd();
        glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
        glRotatef(x, y, z, angle);
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    } else {
        glPushMatrix();
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());
        glBegin(GL_QUADS);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(-100.0, 0.0, -100.0);
        glVertex3f(-100.0, 0.0,  100.0);
        glVertex3f( 100.0, 0.0,  100.0);
        glVertex3f( 100.0, 0.0, -100.0);
        glEnd();
        glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
        glRotatef(x, y, z, angle);
        glPopMatrix();
    }
    return;
}

void Axis::draw()
{
    GLfloat x, y, z, angle;
    this->quat.toGLAxisAngle(x, y, z, angle);
    glPushMatrix();
    glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
    glRotatef(x, y, z, angle);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    /* X axis */
    glBegin(GL_LINES);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3f(0.0 + xyz.x, 0.0, 0.0);
    glVertex3f(5.0 + xyz.x, 0.0, 0.0);
    glEnd();

    /* Y axis */
    glBegin(GL_LINES);
    glColor3d(0.0, 1.0, 0.0);
    glVertex3f(0.0,  0.0 + xyz.y, 0.0);
    glVertex3f(0.0, 5.0 + xyz.y, 0.0);
    glEnd();

    /* Z axis */
    glBegin(GL_LINES);
    glColor3d(0.0, 0.0, 1.0);
    glVertex3f(0.0, 0.0, 0.0 + xyz.z);
    glVertex3f(0.0, 0.0, 5.0 + xyz.z);
    glEnd();

    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    return;
}

Cylinder::Cylinder()
{
    this->quad = gluNewQuadric();
    if(!quad)
        throw;
    return;
}

void Cylinder::draw()
{
    GLfloat radius = 10;
    GLfloat height = 30;
    GLfloat x, y, z, angle;
    this->quat.toGLAxisAngle(x, y, z, angle);
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());
    gluCylinder(this->quad, radius, radius, height, 50, 50);
    glNormal3f(0.0, 0.0, 1.0);
    gluDisk(quad, 0.f, radius, 50, 1);
    glTranslatef(0, 0, height);
    glRotatef(x, y, z, angle);
    glNormal3f(0.0, 0.0, -1.0);
    gluDisk(quad, 0.f, radius, 50, 1);
    glPopMatrix();
    return;
}

Cylinder::~Cylinder()
{
    if(quad)
        gluDeleteQuadric(quad);
}

