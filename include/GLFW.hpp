#pragma once
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <exception>
#include <list>
#include <memory>

#include "Object.hpp"

class GLFW
{
  /* window title and size */
  std::string window_title{"test"};
  int width{1024};
  int height{769};

  GLFWwindow* window;
  std::list<pObject> object_list;

public:
  GLFW();
  ~GLFW();
  void setLight(GLfloat x = 0.f, GLfloat y = 100.f, GLfloat z = -50.f);
  void setLight(const Point& xyz);
  void setCamera();
  void setCamera(const Point& camera_pos, const Point& look_at);
  void run();
  void pushObject(pObject object);
};
