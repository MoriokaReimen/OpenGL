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
// virtual void Object::setAttitude() = 0; implement someday

void Sphere::draw() // protect someday
{
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color.toArray());
  glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
  glutSolidSphere(3, 30, 30);
  glPopMatrix();
  return;
}

void Cube::draw() // protect someday
{
  glPushMatrix();
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color.toArray());
  glTranslatef(this->xyz.x, this->xyz.y, this->xyz.z);
  glutSolidCube(3);
  glPopMatrix();
  return;
}

void Floor::draw() // protect someday
{
  glMaterialfv(GL_FRONT, GL_DIFFUSE, color.toArray());
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
