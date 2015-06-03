cmake_minimum_required(VERSION 2.8)
project(OpenGLTest)
LINK_DIRECTORIES("/usr/local/lib/" "/usr/lib" "/usr/lib/freeglut")
INCLUDE_DIRECTORIES("/usr/local/include/bullet/" "/usr/include/freeglut"
    "include" "resource")
LINK_DIRECTORIES("/usr/local/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "bin")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")

set(OPEN_GL_SRC src/GLObject.cpp src/ObjectColor.cpp src/GLTexture.cpp src/GL.cpp resource/PNG.cpp)

set(BULLET_SRC src/ObjectColor.cpp src/Bullet.cpp src/BulletObject.cpp)


add_executable(OpenGLTest test/GLTest.cpp
    ${OPEN_GL_SRC})
target_link_libraries(OpenGLTest
  pthread stdc++
  GLU GL X11 SOIL glfw GLEW math3d_static)

add_executable(BulletTest test/BulletTest.cpp
    ${BULLET_SRC})
target_link_libraries(BulletTest
  pthread stdc++
  BulletDynamics BulletCollision LinearMath math3d_static)

add_executable(SimulatorTest test/SimulatorTest.cpp
    src/World.cpp
    ${OPEN_GL_SRC}
    ${BULLET_SRC})
target_link_libraries(SimulatorTest
  pthread stdc++
  GLU GL X11 SOIL glfw GLEW
  BulletDynamics BulletCollision LinearMath math3d_static)
