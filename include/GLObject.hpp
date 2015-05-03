#pragma once
#include "ObjectUtil.hpp"
#include "Texture.hpp"
#include <memory>


class GLObject
{
protected:
    Point xyz_ {0, 0, 0};
    // Attitude attitude; implement someday
    ObjectColor color_ {1.f,1.f,1.f};
    Texture texture_;
    Quaternion quat_{1.f, 0.f, 0.f, 0.f};
public:
    GLObject() = default;
    virtual ~GLObject() = default;
    virtual void draw() {};
    virtual void setPosition(double x, double y, double z);
    virtual void setPosition(Point point);
    virtual void setColor(ObjectColor bcolor);
    virtual void setColor(GLfloat r, GLfloat g, GLfloat b);
    virtual void setTexture(Texture& texture);
    virtual void setAttitude(const Quaternion& quat);
};

class GLSphere : public GLObject
{
protected:
  GLfloat radius_{10};
public:
    virtual void draw() override; // protect someday
    virtual void setSize(const GLfloat& bradius);
};

class GLCube : public GLObject
{
protected:
  GLfloat a_{10};
  GLfloat b_{10};
  GLfloat c_{10};
public:
    virtual void draw() override; // protect someday
    virtual void setSize(const GLfloat& a, const GLfloat& b, const GLfloat& c);
};

class GLFloor : public GLObject
{
protected:
  GLfloat a_{10};
  GLfloat b_{10};
public:
    virtual void draw() override; // protect someday
    virtual void setSize(const GLfloat& a, const GLfloat& b);
};

class GLAxis : public GLObject
{
protected:
  GLfloat width_{10};
  GLfloat length_{10};
public:
    virtual void draw() override;
    virtual void setSize(const GLfloat& width, const GLfloat& length);
};

class GLCylinder : public GLObject
{
  GLfloat radius_{10};
  GLfloat height_{10};
public:
    virtual void draw() override;
    virtual void setSize(const GLfloat& radius, const GLfloat& height);
};

typedef std::shared_ptr<GLSphere> pGLSphere;
typedef std::shared_ptr<GLObject> pGLObject;
typedef std::shared_ptr<GLFloor> pGLFloor;
typedef std::shared_ptr<GLAxis> pGLAxis;
typedef std::shared_ptr<GLCylinder> pGLCylinder;
typedef std::shared_ptr<GLCube> pGLCube;
