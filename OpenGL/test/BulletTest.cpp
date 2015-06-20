#include <iostream>
#include "Bullet.hpp"

int main()
{
    Math3D::Vector3 h(0, 0, 100), zero(0, 0, 10);
    Math3D::Quaternion quat(0, 0, 0, 1);
  Bullet bullet;
  BulletSphere* sphere = new BulletSphere(h, quat, 10.0, 1.0);
  BulletPlane* plane = new BulletPlane(zero, quat);
  bullet.pushObject(sphere);
  bullet.pushObject(plane);
  for(int i = 0; i < 300; ++i)
  {
    bullet.step();
    Math3D::Vector3 xyz = sphere->getPoint();
    std::cout << bullet.time << ", " << xyz.z << std::endl;
  }
  return 0;
}
