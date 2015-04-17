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
    this->quat.toGLAngleAxis(angle, x, y, z);
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());
    glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
    glRotatef(angle, x, y, z);
    for(int i = 0; i <= 30; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / 30);
        double z0  = sin(lat0);
        double zr0 =  cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / 30);
        double z1 = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(int j = 0; j <= 30; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / 30;
            double x = cos(lng);
            double y = sin(lng);

            glNormal3f(x * zr0, y * zr0, z0);
            glVertex3f(x * zr0, y * zr0, z0);
            glNormal3f(x * zr1, y * zr1, z1);
            glVertex3f(x * zr1, y * zr1, z1);
        }
        glEnd();
    }
    glPopMatrix();
    return;
}

void Cube::draw() // protect someday
{
  GLfloat x, y, z, angle;
  this->quat.toGLAngleAxis(angle, x, y, z);
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());
  glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
  glRotatef(angle, x, y, z);

  GLfloat lx = 30.0 * 0.5f; // modify some day
  GLfloat ly = 30.0 * 0.5f;
  GLfloat lz = 30.0 * 0.5f;

  // sides
  glBegin (GL_TRIANGLE_STRIP);
  glNormal3f (-1,0,0);
  glVertex3f (-lx,-ly,-lz);
  glVertex3f (-lx,-ly,lz);
  glVertex3f (-lx,ly,-lz);
  glVertex3f (-lx,ly,lz);
  glNormal3f (0,1,0);
  glVertex3f (lx,ly,-lz);
  glVertex3f (lx,ly,lz);
  glNormal3f (1,0,0);
  glVertex3f (lx,-ly,-lz);
  glVertex3f (lx,-ly,lz);
  glNormal3f (0,-1,0);
  glVertex3f (-lx,-ly,-lz);
  glVertex3f (-lx,-ly,lz);
  glEnd();

  // top face
  glBegin (GL_TRIANGLE_FAN);
  glNormal3f (0,0,1);
  glVertex3f (-lx,-ly,lz);
  glVertex3f (lx,-ly,lz);
  glVertex3f (lx,ly,lz);
  glVertex3f (-lx,ly,lz);
  glEnd();

  // bottom face
  glBegin (GL_TRIANGLE_FAN);
  glNormal3f (0,0,-1);
  glVertex3f (-lx,-ly,-lz);
  glVertex3f (-lx,ly,-lz);
  glVertex3f (lx,ly,-lz);
  glVertex3f (lx,-ly,-lz);
  glEnd();

  glPopMatrix();
  return;
}

void Floor::draw() // protect someday
{
    GLfloat x, y, z, angle;
    this->quat.toGLAngleAxis(angle, x, y, z);
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
        glRotatef(angle, x, y, z);
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
        glRotatef(angle, x, y, z);
        glPopMatrix();
    }
    return;
}

void Axis::draw()
{
    GLfloat x, y, z, angle;
    this->quat.toGLAngleAxis(angle, x, y, z);
    glPushMatrix();
    glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
    glRotatef(angle, x, y, z);
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
    GLfloat height = 20;
    GLfloat x, y, z, angle;
    this->quat.toGLAngleAxis(angle, x, y, z);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());

    glPushMatrix();
    //glTranslatef(0, 0, height / 2);
    glRotatef(angle, x, y, z);
    glTranslatef(0, 0, - height / 2);
    gluCylinder(this->quad, radius, radius, height, 50, 50);
    glPopMatrix();

    // draw top
    glPushMatrix();
    glRotatef(angle, x, y, z);
    glNormal3f(0.0, 0.0, 1.0);
    glTranslatef(0, 0, height/2);
    gluDisk(quad, 0.f, radius, 50, 1);
    glPopMatrix();

    // draw base
    glPushMatrix();
    glRotatef(angle, x, y, z);
    glNormal3f(0.0, 0.0, -1.0);
    glTranslatef(0, 0, -height/2);
    gluDisk(quad, 0.f, radius, 50, 1);
    glPopMatrix();

    return;
}

Cylinder::~Cylinder()
{
    if(quad)
        gluDeleteQuadric(quad);
}

