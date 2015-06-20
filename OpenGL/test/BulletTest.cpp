#include <iostream>
#include "Bullet.hpp"

int main()
{
    Math3D::Vector3 h(0, 0, 100);
    Math3D::Quaternion quat;
  Bullet bullet;
  BulletSphere* sphere = new BulletSphere(h, quat, 10.0, 1.0);
  bullet.pushObject(sphere);
  for(int i = 0; i < 10000; ++i)
  {
    bullet.step();
    Math3D::Vector3 xyz = sphere->getPoint();
    std::cout << xyz.z << std::endl;
  }
  return 0;
}
