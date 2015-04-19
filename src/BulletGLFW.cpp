#include "BulletGLFW.hpp"
BulletGLFW::BulletGLFW()
  : GLFW()
{
  this->broadphase = new btDbvtBroadphase();
  this->collisionConfiguration = new btDefaultCollisionConfiguration();
  this->dispatcher = new btCollisionDispatcher(collisionConfiguration);
  this->solver = new btSequentialImpulseConstraintSolver;
  this->dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

  this->dynamicsWorld->setGravity(btVector3(0, 0, - this->gravity));

  return;
}

BulletGLFW::~BulletGLFW()
{
  delete this->dynamicsWorld;
  delete this->solver;
  delete this->collisionConfiguration;
  delete this->dispatcher;
  delete this->broadphase;

  return;
}

void BulletGLFW::run()
{
  do {
    this->dynamicsWorld->stepSimulation(1/ 60.f, 10);
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
