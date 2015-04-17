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
    glTranslatef(this->xyz.x, this->xyz.z, this->xyz.y);
    glRotatef(angle, x, y, z);
    for(int i = 0; i <= 30; i++) {
        double lat0 = M_PI * (-0.5 + (double) (i - 1) / 30);
        double z0  = sin(lat0);
        double zr0 = cos(lat0);

        double lat1 = M_PI * (-0.5 + (double) i / 30);
        double z1  = sin(lat1);
        double zr1 = cos(lat1);

        glBegin(GL_QUAD_STRIP);
        for(int j = 0; j <= 30; j++) {
            double lng = 2 * M_PI * (double) (j - 1) / 30;
            double rx = cos(lng);
            double ry = sin(lng);

            glNormal3f(rx * zr0, ry * zr0, z0);
            glVertex3f(this->radius * rx * zr0, this->radius * ry * zr0, this->radius * z0);
            glNormal3f(rx * zr1, ry * zr1, z1);
            glVertex3f(this->radius * rx * zr1, this->radius * ry * zr1, this->radius * z1);
        }
        glEnd();
    }
    glPopMatrix();
    return;
}

void Sphere::setSize(const GLfloat& bradius)
{
  this->radius = bradius;
  return;
}

void Cube::draw() // protect someday
{
  GLfloat x, y, z, angle;
  this->quat.toGLAngleAxis(angle, x, y, z);
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());
  glTranslatef(this->xyz.x, this->xyz.z, this->xyz.y);
  glRotatef(angle, x, y, z);

  GLfloat la = this->a * 0.5f; // modify some day
  GLfloat lb = this->b * 0.5f;
  GLfloat lc = this->c * 0.5f;

  // sides
  glBegin (GL_TRIANGLE_STRIP);
  glNormal3f(-1,0,0);
  glVertex3f(-la, -lc, -lb);
  glVertex3f(-la, -lc,  lb);
  glVertex3f(-la,  lc, -lb);
  glVertex3f(-la,  lc,  lb);
  glNormal3f(0,1,0);
  glVertex3f( la,  lc, -lb);
  glVertex3f( la,  lc,  lb);
  glNormal3f(1,0,0);
  glVertex3f(la, -lc, -lb);
  glVertex3f(la, -lc,  lb);
  glNormal3f(0,-1,0);
  glVertex3f(-la, -lc, -lb);
  glVertex3f(-la, -lc,  lb);
  glEnd();

  // top face
  glBegin (GL_TRIANGLE_FAN);
  glNormal3f(0,0,1);
  glVertex3f(-la, -lc,  lb);
  glVertex3f( la, -lc,  lb);
  glVertex3f( la,  lc,  lb);
  glVertex3f(-la,  lc,  lb);
  glEnd();

  // bottom face
  glBegin (GL_TRIANGLE_FAN);
  glNormal3f(0,0,-1);
  glVertex3f(-la, -lc, -lb);
  glVertex3f(-la,  lc, -lb);
  glVertex3f( la,  lc, -lb);
  glVertex3f( la, -lc, -lb);
  glEnd();

  glPopMatrix();
  return;
}

void Cube::setSize(const GLfloat& ba, const GLfloat& bb, const GLfloat& bc)
{
  this->a = ba;
  this->b = bb;
  this->c = bc;
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
        glTranslatef(this->xyz.x, this->xyz.z, this->xyz.y);
        glRotatef(angle, x, y, z);
        glBegin (GL_TRIANGLE_FAN);
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.f, 0.f);
        glVertex3f(this->a/2, 0.0, - this->b/2);
        glTexCoord2f(0.f, 5.f);
        glVertex3f(this->a/2, 0.0, this->b/2);
        glTexCoord2f(5.f, 5.f);
        glVertex3f(- this->a/2, 0.0,  this->b/2);
        glTexCoord2f(5.f, 0.f);
        glVertex3f(- this->a/2, 0.0, - this->b/2);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    } else {
        glPushMatrix();
        glTranslatef(this->xyz.x, this->xyz.z, this->xyz.y);
        glRotatef(angle, x, y, z);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());
        glBegin (GL_TRIANGLE_FAN);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(this->a/2, 0.0, - this->b/2);
        glVertex3f(this->a/2, 0.0, this->b/2);
        glVertex3f(- this->a/2, 0.0,  this->b/2);
        glVertex3f(- this->a/2, 0.0, - this->b/2);
        glEnd();
        glPopMatrix();
    }
    return;
}

void Floor::setSize(const GLfloat& ba, const GLfloat& bb)
{
  this->a = ba;
  this->b = bb;
  return;
}

void Axis::draw()
{
    GLfloat x, y, z, angle;
    this->quat.toGLAngleAxis(angle, x, y, z);
    glPushMatrix();
    glTranslatef(this->xyz.x, this->xyz.z, this->xyz.y);
    glRotatef(angle, x, y, z);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glLineWidth(this->width);

    /* X axis */
    glBegin(GL_LINES);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3f(0.0 + xyz.x, 0.0, 0.0);
    glVertex3f(this->length + xyz.x, 0.0, 0.0);
    glEnd();

    /* Y axis */
    glBegin(GL_LINES);
    glColor3d(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0 + xyz.y);
    glVertex3f(0.0, 0.0, this->length + xyz.y);
    glEnd();

    /* Z axis */
    glBegin(GL_LINES);
    glColor3d(0.0, 0.0, 1.0);
    glVertex3f(0.0,  0.0 + xyz.z, 0.0);
    glVertex3f(0.0, this->length + xyz.z, 0.0);
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    return;
}

void Axis::setSize(const GLfloat& bwidth, const GLfloat& blength)
{
  this->width = bwidth;
  this->length = blength;
  return;
}

void Cylinder::draw()
{
    GLfloat x, y, z, angle;
    float tmp,ny,nz;
    const int sides = 24;     // number of sides to the cylinder (divisible by 4)
    this->quat.toGLAngleAxis(angle, x, y, z);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, color.toArray());

    glPushMatrix();
    glTranslatef(this->xyz.x, this->xyz.z, this->xyz.y);
    glRotatef(angle, x, y, z);


  float a = float(M_PI*2.0)/float(sides);
  float sa = std::sin(a);
  float ca = std::cos(a);

  // draw cylinder body
  ny=1; nz=0;             // normal vector = (0,ny,nz)
  glBegin (GL_TRIANGLE_STRIP);
  for (int i=0; i<=sides; i++) {
    glNormal3d(ny,nz,0);
    glVertex3d(ny*radius, nz*radius, height / 2);
    glNormal3d(ny, nz, 0);
    glVertex3d(ny*radius, nz*radius, -height / 2);
    // rotate ny,nz
    tmp = ca*ny - sa*nz;
    nz = sa*ny + ca*nz;
    ny = tmp;
  }
  glEnd();

  // draw top cap
  ny=1; nz=0;             // normal vector = (0,ny,nz)
  glBegin (GL_TRIANGLE_FAN);
  glNormal3d (0,0,1);
  glVertex3d (0,0,height / 2);
  for (int i=0; i<=sides; i++) {
    glNormal3d (0,0,1);
    glVertex3d (ny*radius,nz*radius,height / 2);

    // rotate ny,nz
    tmp = ca*ny - sa*nz;
    nz = sa*ny + ca*nz;
    ny = tmp;
  }
  glEnd();

  // draw bottom cap
  ny=1; nz=0;             // normal vector = (0,ny,nz)
  glBegin (GL_TRIANGLE_FAN);
  glNormal3d (0,0,-1);
  glVertex3d (0,0,-height / 2);
  for (int i=0; i<=sides; i++) {
    glNormal3d (0,0,-1);
    glVertex3d (ny*radius,nz*radius,-height / 2);

    // rotate ny,nz
    tmp = ca*ny + sa*nz;
    nz = -sa*ny + ca*nz;
    ny = tmp;
  }
  glEnd();
  glPopMatrix();

  return;
}

void Cylinder::setSize(const GLfloat& bradius, const GLfloat& bheight)
{
  this->radius = bradius;
  this->height = bheight;
}
