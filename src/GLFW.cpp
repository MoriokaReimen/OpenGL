#include "GLFW.hpp"

GLFW::GLFW()
  {
    /* Initialize glfw */
    if(!glfwInit()) throw std::runtime_error("Failed to Init glfw");
    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    this->window = glfwCreateWindow(this->width, this->height, this->window_title.c_str(), NULL, NULL);
    //this->window = glfwCreateWindow(640, 640, this->window_title.c_str(), NULL, NULL);
    if( window == NULL ) throw std::runtime_error("Failed to Open window");
    glfwMakeContextCurrent(this->window);

    /* Initialize glew */
    if(glewInit() != GLEW_OK) std::runtime_error("Failed to Init glew");

    // Ensure we can capture the escape key being pressed below
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);

    /* Set Background Color and Depth Buffer */
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClearDepth(1.0);
    glEnable(GL_DEPTH_TEST);

    return;
  }

GLFW::~GLFW()
  {
    glfwTerminate();
  }

  void GLFW::setLight(GLfloat x, GLfloat y, GLfloat z)
  {
      GLfloat lightpos[4];
      lightpos[0] = x;
      lightpos[1] = y;
      lightpos[2] = z;
      lightpos[3] = 1.f;

      glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);
      return;
  }

  void GLFW::setLight(const Point& xyz)
  {
      GLfloat lightpos[4];
      lightpos[0] = xyz.x;
      lightpos[1] = xyz.y;
      lightpos[2] = xyz.z;
      lightpos[3] = 1.f;

      glLightfv(GL_LIGHT0, GL_POSITION, lightpos);
      glEnable(GL_LIGHT0);
      glEnable(GL_LIGHTING);
      glEnable(GL_NORMALIZE);
      return;
  }

  void GLFW::setCamera()
  {
    //視点の設定
    glViewport(0, 0, this->width, this->height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f, (float)this->width/(float)this->height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(0.0,20,-50, //カメラの座標
              0.0,0.0,0.0, // 注視点の座標
              0.0,1.0,0.0); // 画面の上方向を指すベクトル
    return;
  }

  void GLFW::setCamera(const Point& camera_pos, const Point& look_at)
  {
    //視点の設定
    glViewport(0, 0, this->width, this->height);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(60.f, (float)this->width/(float)this->height, 0.1f, 100.0f);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    gluLookAt(camera_pos.x, camera_pos.y, camera_pos.z, //カメラの座標
              look_at.x, look_at.y, look_at.z, // 注視点の座標
              0.0,1.0,0.0); // 画面の上方向を指すベクトル
    return;
  }

  void GLFW::run()
  {
    do {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    for(auto it = this->object_list.begin(); it != this->object_list.end(); ++it) {
        (*it) -> draw();
    }
      glfwSwapBuffers(window);
      glfwPollEvents();

      if(glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GL_FALSE);

    } while(!glfwWindowShouldClose(window));
  }

  void GLFW::pushObject(pObject object)
  {
    this->object_list.push_back(object);
    return;
  }














