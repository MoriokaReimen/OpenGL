#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <list>
#include <memory>

#include "Object.hpp"

class GLFW
{
protected:
  /* window title and size */
  std::string window_title{"test"};
  int width{1024};
  int height{769};

  GLFWwindow* window;
  std::list<pObject> object_list;

public:
  GLFW();
  ~GLFW();
  virtual void setLight(GLfloat x = 0.f, GLfloat y = 100.f, GLfloat z = -50.f);
  virtual void setLight(const Point& xyz);
  virtual void setCamera();
  virtual void setCamera(const Point& camera_pos, const Point& look_at);
  virtual void run();
  virtual void pushObject(pObject object);
};
