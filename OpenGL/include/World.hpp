#pragma once
#include <Math3D/Math3D.hpp>
#include "GL.hpp"
#include "Bullet.hpp"

class World
{
  GL* gl;
  Bullet* bullet;
public:
  World();
  virtual ~World();
  void setLight(GLfloat x, GLfloat y, GLfloat z);
  void setLight(const Math3D::Vector3& xyz);
  void setCamera();
  void setCamera(const Math3D::Vector3& camera_pos, const Math3D::Vector3& look_at);
  void run();
  void pushObject(Object* object);
  void display();
};
