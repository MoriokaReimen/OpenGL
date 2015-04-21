#include <iostream>
#include "BaseBullet.hpp"

int main()
{
  BaseBullet bullet;
  BaseBulletSphereFactory factory;
  factory.xyz.z = 100;
  pBaseBulletObject sphere = factory.spawn();
  //sphere->init();
  bullet.pushObject(sphere);
  for(int i = 0; i < 100; ++i)
  {
    bullet.step();
    Point xyz = sphere->getPoint();
    std::cout << xyz.z << std::endl;
  }
  return 0;
}
