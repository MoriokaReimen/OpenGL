#include "GLObject.hpp"

void GLObject::setPosition(double x, double y, double z)
{
    Math3D::Vector3 buff(x, y, z);
    this->xyz_ = buff;
    return;
}

void GLObject::setPosition(Math3D::Vector3 point)
{
    this->xyz_ = point;
    return;
}

void GLObject::setColor(GLColor color)
{
    this->color_ = color;
    return;
}

void GLObject::setColor(GLfloat r, GLfloat g, GLfloat b)
{
    this->color_.r = r;
    this->color_.g = g;
    this->color_.b = b;
    return;
}

void GLObject::setAttitude(const Math3D::Quaternion& quat)
{
    this->quat_ = quat;
    return;
}

void GLObject::setTexture(GLTexture& texture)
{
    this->texture_ = texture;
    return;
}

void GLSphere::draw() // protect someday
{
    Math3D::Degree angle;
    Math3D::Vector3 axis;
    this->quat_.toAngleAxis(angle, axis);
    glPushMatrix();
    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->color_.toArray());
    glTranslatef(this->xyz_.x, this->xyz_.y, this->xyz_.z);
    glRotatef(angle, axis.x,  axis.y,  axis.z);
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
            glVertex3f(this->radius_ * rx * zr0, this->radius_ * ry * zr0, this->radius_ * z0);
            glNormal3f(rx * zr1, ry * zr1, z1);
            glVertex3f(this->radius_ * rx * zr1, this->radius_ * ry * zr1, this->radius_ * z1);
        }
        glEnd();
    }
    glPopMatrix();
    return;
}

void GLSphere::setSize(const GLfloat& radius)
{
  this->radius_ = radius;
  return;
}

void GLBox::draw() // protect someday
{
    Math3D::Degree angle;
    Math3D::Vector3 axis;
    this->quat_.toAngleAxis(angle, axis);
  glPushMatrix();
  glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->color_.toArray());
    glTranslatef(this->xyz_.x, this->xyz_.y, this->xyz_.z);
    glRotatef(angle, axis.x, axis.y, axis.z);

  GLfloat la = this->a_; // modify some day
  GLfloat lb = this->b_;
  GLfloat lc = this->c_;

  // sides
  glBegin (GL_TRIANGLE_STRIP);
  glNormal3f(-1,0,0);
  glVertex3f(0, 0, 0);
  glVertex3f(0,  lb, 0);
  glVertex3f(0,  lb,  lc);
  glVertex3f(0, 0,  lc);
  glEnd();

  glBegin (GL_TRIANGLE_FAN);
  glNormal3f(0,0,1);
  glVertex3f(la, lb, lc);
  glVertex3f(la, 0,  lc);
  glVertex3f(0, 0,  lc);
  glVertex3f( 0,  lb,  lc);
  glEnd();

  glBegin (GL_TRIANGLE_FAN);
  glNormal3f(0,0,-1);
  glVertex3f(0, 0, 0);
  glVertex3f(la, 0,  0);
  glVertex3f(la, lb, 0);
  glVertex3f( 0,  lb, 0);
  glEnd();

  glBegin (GL_TRIANGLE_FAN);
  glNormal3f(1,0,0);
  glVertex3f(la, 0, 0);
  glVertex3f(la, 0, lc);
  glVertex3f(la, lb, lc);
  glVertex3f(la, lb, 0);
  glEnd();

  // top face
  glBegin (GL_TRIANGLE_FAN);
  glNormal3f(0,1,0);
  glVertex3f(0, lb,  0);
  glVertex3f( la, lb, 0);
  glVertex3f( la,  lb,  lc);
  glVertex3f(0,  lb,  lc);
  glEnd();

  // bottom face
  glBegin (GL_TRIANGLE_FAN);
  glNormal3f( 0,  -1, 0);
  glVertex3f( 0, 0, 0);
  glVertex3f(la, 0, 0);
  glVertex3f(la, 0, lc);
  glVertex3f(0, 0, lc);
  glEnd();

  glPopMatrix();
  return;
}

void GLBox::setSize(const GLfloat& a, const GLfloat& b, const GLfloat& c)
{
  this->a_ = a;
  this->b_ = b;
  this->c_ = c;
  return;
}

void GLPlane::draw() // protect someday
{
    Math3D::Degree angle;
    Math3D::Vector3 axis;
    this->quat_.toAngleAxis(angle, axis);
    if(this->texture_.getID()) {
        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, this->texture_.getID());
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->color_.toArray());
        glPushMatrix();
    glTranslatef(this->xyz_.x, this->xyz_.y, this->xyz_.z);
    glRotatef(angle, axis.x, axis.y, axis.z);
        glBegin (GL_TRIANGLE_FAN);
        glNormal3f(0.0, 1.0, 0.0);
        glTexCoord2f(0.f, 0.f);
        glVertex3f(this->a_/2, 0.0, - this->b_/2);
        glTexCoord2f(0.f, 5.f);
        glVertex3f(this->a_/2, 0.0, this->b_/2);
        glTexCoord2f(5.f, 5.f);
        glVertex3f(- this->a_/2, 0.0,  this->b_/2);
        glTexCoord2f(5.f, 0.f);
        glVertex3f(- this->a_/2, 0.0, - this->b_/2);
        glEnd();
        glPopMatrix();
        glDisable(GL_TEXTURE_2D);
    } else {
        glPushMatrix();
    glTranslatef(this->xyz_.x, this->xyz_.y, this->xyz_.z);
    glRotatef(angle, axis.x, axis.y, axis.z);
        glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->color_.toArray());
        glBegin (GL_TRIANGLE_FAN);
        glNormal3f(0.0, 1.0, 0.0);
        glVertex3f(  this->a_/2, 0.0, - this->b_/2);
        glVertex3f(  this->a_/2, 0.0, this->b_/2);
        glVertex3f(- this->a_/2, 0.0,  this->b_/2);
        glVertex3f(- this->a_/2, 0.0, - this->b_/2);
        glEnd();
        glPopMatrix();
    }
    return;
}

void GLPlane::setSize(const GLfloat& a, const GLfloat& b)
{
  this->a_ = a;
  this->b_ = b;
  return;
}

void GLAxis::draw()
{
    Math3D::Degree angle;
    Math3D::Vector3 axis;
    this->quat_.toAngleAxis(angle, axis);
    glPushMatrix();
    glTranslatef(this->xyz_.x, this->xyz_.y, this->xyz_.z);
    glRotatef(angle, axis.x, axis.y, axis.z);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHTING);

    glLineWidth(this->width_);

    /* X axis */
    glBegin(GL_LINES);
    glColor3d(1.0, 0.0, 0.0);
    glVertex3f(0.0 + this->xyz_.x, 0.0, 0.0);
    glVertex3f(this->length_ + this->xyz_.x, 0.0, 0.0);
    glEnd();

    /* Y axis */
    glBegin(GL_LINES);
    glColor3d(0.0, 1.0, 0.0);
    glVertex3f(0.0, 0.0, 0.0 + this->xyz_.y);
    glVertex3f(0.0, 0.0, this->length_ + this->xyz_.y);
    glEnd();

    /* Z axis */
    glBegin(GL_LINES);
    glColor3d(0.0, 0.0, 1.0);
    glVertex3f(0.0,  0.0 + this->xyz_.z, 0.0);
    glVertex3f(0.0, this->length_ + this->xyz_.z, 0.0);
    glEnd();


    glDisable(GL_COLOR_MATERIAL);
    glEnable(GL_LIGHTING);
    glPopMatrix();
    return;
}

void GLAxis::setSize(const GLfloat& width, const GLfloat& length)
{
  this->width_  = width;
  this->length_ = length;
  return;
}

void GLCylinder::draw()
{
    Math3D::Degree angle;
    Math3D::Vector3 axis;
    float tmp,ny,nz;
    const int sides = 24;     // number of sides to the cylinder (divisible by 4)
    this->quat_.toAngleAxis(angle, axis);

    glMaterialfv(GL_FRONT_AND_BACK, GL_DIFFUSE, this->color_.toArray());

    glPushMatrix();
    glTranslatef(this->xyz_.x, this->xyz_.y, this->xyz_.z);
    glRotatef(angle, axis.x, axis.y, axis.z);


  float a = float(M_PI*2.0)/float(sides);
  float sa = std::sin(a);
  float ca = std::cos(a);

  // draw cylinder body
  ny=1; nz=0;             // normal vector = (0,ny,nz)
  glBegin (GL_TRIANGLE_STRIP);
  for (int i=0; i<=sides; i++) {
    glNormal3d(ny,nz,0);
    glVertex3d(ny * this->radius_, nz * this->radius_,   this->height_ / 2);
    glNormal3d(ny, nz, 0);
    glVertex3d(ny * this->radius_, nz * this->radius_, - this->height_ / 2);
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
  glVertex3d (0,0,this->height_ / 2);
  for (int i=0; i<=sides; i++) {
    glNormal3d (0,0,1);
    glVertex3d (ny * this->radius_, nz * this->radius_, this->height_ / 2);

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
  glVertex3d (0,0,- this->height_ / 2);
  for (int i=0; i<=sides; i++) {
    glNormal3d (0,0,-1);
    glVertex3d (ny * this->radius_, nz * this->radius_, - this->height_ / 2);

    // rotate ny,nz
    tmp = ca*ny + sa*nz;
    nz = -sa*ny + ca*nz;
    ny = tmp;
  }
  glEnd();
  glPopMatrix();

  return;
}

void GLCylinder::setSize(const GLfloat& radius, const GLfloat& height)
{
  this->radius_ = radius;
  this->height_ = height;
}
