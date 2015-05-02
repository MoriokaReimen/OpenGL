class BulletGL
{
  GLFW glfw;
  BaseBullet bullet;
public:
  BulletGL() :
    glfw(), bullet()
  {
    return;
  }

  virtual ~BulletGL()
  {
    this->glfw->~GLFW();
    this->bullet->~BaseBullet();
    return;
  }

  void setLight(GLfloat x, GLfloat y, GLfloat z)
  {
    this->glfw->setLight(x, y, z);
    return;
  }

  void setLight(const Point& xyz)
  {
    this->glfw->setLight(xyz);
    return;
  }

  void setCamera()
  {
    this->glfw->setCamera();
    return;
  }

  void setCamera(const Point& camera_pos, const Point& look_at)
  {
    this->glfw->setCamera(camera_pos, look_at)
    return;
  }

  void run()
  {
    do {
      this->glfw->display();
      this->bullet->step();
    } while(!glfwWindowShouldClose(this->glfw->window_));
  }

  void pushObject(pBulletGLObject object)
  {
    this->glfw->pushObject(object->gl_object);
    this->bullet->pushObject(object->bullet_object);
    return;
  }

  void display()
  {
    this->glfw->display();
    this->bullet->step();
    return;
  }

};
