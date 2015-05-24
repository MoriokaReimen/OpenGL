#pragma once
#include "GL.hpp"
#include "Bullet.hpp"

class World
{
  GL gl{};
  Bullet bullet{};
public:
  World();
  virtual ~World();
  void setLight(GLfloat x, GLfloat y, GLfloat z);
  void setLight(const Point& xyz);
  void setCamera();
  void setCamera(const Point& camera_pos, const Point& look_at);
  void run();
  //void pushObject(pBulletGLObject object);
  void display();
};
