#include <iostream>
#include "Bullet.hpp"

int main()
{
    Math3D::Vector3 h(0, 0, 100), zero(0, 0, 0);
    Math3D::Quaternion quat(0, 0, 0, 1);
  Bullet bullet;
  BulletSphere* sphere = new BulletSphere(10.0, 3.0);
  BulletPlane* plane = new BulletPlane();
  plane->setPosition(zero);
  sphere->setPosition(h);
  bullet.pushObject(sphere);
  bullet.pushObject(plane);
  for(int i = 0; i < 1; ++i)
  {
    bullet.step();
    Math3D::Vector3 xyz = sphere->getPosition();
    std::cout << bullet.time << ", " << xyz.z << std::endl;
  }
  delete sphere;
  delete plane;
  return 0;
}
