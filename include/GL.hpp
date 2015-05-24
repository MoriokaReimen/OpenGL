#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <list>
#include <memory>

#include "GLObject.hpp"

class GL
{
protected:
  /* window title and size */
  std::string window_title_{"test"};
  int width_{1024};
  int height_{769};

  GLFWwindow* window_;
  std::list<pGLObject> object_list_;

public:
  GL();
  ~GL();
  virtual void setLight(GLfloat x = 0.f, GLfloat y = 100.f, GLfloat z = -50.f);
  virtual void setLight(const Point& xyz);
  virtual void setCamera();
  virtual void setCamera(const Point& camera_pos, const Point& look_at);
  virtual void run();
  virtual void pushObject(pGLObject object);
  virtual void display();
  virtual bool isClose();
};
