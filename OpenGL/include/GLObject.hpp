#pragma once
#include <Math3D/Math3D.hpp>
#include "GLTexture.hpp"
#include "GLColor.hpp"
#include <memory>


class GLObject
{
protected:
    Math3D::Vector3 xyz_ {0, 0, 0};
    // Attitude attitude; implement someday
    GLColor color_ {1.f,1.f,1.f};
    GLTexture texture_;
    Math3D::Quaternion quat_{1.f, 0.f, 0.f, 0.f};
public:
    GLObject() = default;
    virtual ~GLObject() = default;
    virtual void draw() {};
    virtual void setPosition(double x, double y, double z);
    virtual void setPosition(Math3D::Vector3 point);
    virtual void setColor(GLColor bcolor);
    virtual void setColor(GLfloat r, GLfloat g, GLfloat b);
    virtual void setTexture(GLTexture& texture);
    virtual void setAttitude(const Math3D::Quaternion& quat);
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

class GLPlane : public GLObject
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
typedef std::shared_ptr<GLPlane> pGLPlane;
typedef std::shared_ptr<GLAxis> pGLAxis;
typedef std::shared_ptr<GLCylinder> pGLCylinder;
typedef std::shared_ptr<GLCube> pGLCube;
