cmake_minimum_required(VERSION 2.8)
project(OpenGLTest)
add_subdirectory(src)
add_subdirectory(spike)
add_subdirectory(test)
add_subdirectory(resource)
add_subdirectory(bin)
add_subdirectory(include)
LINK_DIRECTORIES("/usr/local/lib/" "/usr/lib" "/usr/lib/freeglut")
INCLUDE_DIRECTORIES("/usr/include" "/usr/local/include/bullet" "/usr/include/freeglut"
    "${CMAKE_BINARY_DIR}/include"
    "${CMAKE_BINARY_DIR}/resource")
LINK_DIRECTORIES("/usr/local/lib")
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin")
set(CMAKE_CXX_FLAGS "-std=c++11 -Wall -g")

add_executable(OpenGLTest test/GLTest.cpp
  src/GLObject.cpp
  src/3dMath.cpp
  src/GLTexture.cpp
  src/GL.cpp
  resource/PNG.cpp)
target_link_libraries(OpenGLTest
  pthread stdc++
  GLU GL X11 SOIL glfw GLEW)

add_executable(BulletTest test/BulletTest.cpp
  src/3dMath.cpp
  src/Bullet.cpp
  src/BulletObject.cpp)
target_link_libraries(BulletTest
  pthread stdc++
  BulletDynamics BulletCollision LinearMath)

add_executable(SimulatorTest test/SimulatorTest.cpp
    src/World.cpp
    src/GLObject.cpp
    src/3dMath.cpp
    src/GLTexture.cpp
    src/GL.cpp
    resource/PNG.cpp
    src/3dMath.cpp
    src/Bullet.cpp
    src/BulletObject.cpp)
target_link_libraries(SimulatorTest
  pthread stdc++
  GLU GL X11 SOIL glfw GLEW
  BulletDynamics BulletCollision LinearMath)
