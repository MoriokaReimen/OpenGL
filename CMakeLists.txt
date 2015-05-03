cmake_minimum_required(VERSION 2.8)
project(OpenGLTest)
add_subdirectory(src)
add_subdirectory(spike)
add_subdirectory(resource)
add_subdirectory(bin)
add_subdirectory(include)
LINK_DIRECTORIES("/usr/local/lib/" "/usr/lib" "/usr/lib/freeglut")
INCLUDE_DIRECTORIES("/usr/include" "/usr/local/include/bullet" "/usr/include/freeglut" "${CMAKE_BINARY_DIR}/include")
LINK_DIRECTORIES("/usr/local/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")

add_executable(OpenGLTest src/main.cpp
  src/GLObject.cpp include/GLObject.hpp
  src/GLObjectUtil.cpp include/GLObjectUtil.hpp
  src/GLTexture.cpp include/GLTexture.hpp
  src/GL.cpp include/GL.hpp)
target_link_libraries(OpenGLTest
  pthread stdc++
  GLU GL X11 SOIL glfw GLEW
  BulletDynamics BulletCollision LinearMath)

add_executable(BulletTest src/bullet_test.cpp
  src/GLObjectUtil.cpp include/GLObjectUtil.hpp
  src/BaseBullet.cpp include/BaseBullet.hpp
  src/BaseBulletObject.cpp include/BaseBulletObject.hpp)
target_link_libraries(BulletTest
  pthread stdc++
  GLU GL X11 SOIL glfw GLEW
  BulletDynamics BulletCollision LinearMath)
