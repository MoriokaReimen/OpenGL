#include <iostream>
#include "Bullet.hpp"

int main()
{
  Bullet bullet;
  BulletObjectFactory::xyz.z = 100;
  pBulletObject sphere = BulletObjectFactory::spawnSphere(10.0);
  bullet.pushObject(sphere);
  for(int i = 0; i < 100; ++i)
  {
    bullet.step();
    Math3D::Vector3 xyz = sphere->getPoint();
    std::cout << xyz.z << std::endl;
  }
  return 0;
}
