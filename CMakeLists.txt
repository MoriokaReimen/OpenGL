cmake_minimum_required(VERSION 2.8)
# include math3d
project(Math3D)
include(ExternalProject)
ExternalProject_Add(MATH3D
    PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/external/Math3D
    GIT_REPOSITORY "https://github.com/MoriokaReimen/Math.git"
    GIT_TAG "master"
    INSTALL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/external/Math3D
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/external)

include_directories(${CMAKE_CURRENT_SOURCE_DIR}/external/include)

# build mains

project(OpenGLTest)
LINK_DIRECTORIES("/usr/local/lib/" "/usr/lib" "/usr/lib/freeglut")
INCLUDE_DIRECTORIES("/usr/local/include/bullet" "/usr/include/freeglut"
    "${CMAKE_SOURCE_DIR}/include"
    "${CMAKE_SOURCE_DIR}/external/include"
    "${CMAKE_SOURCE_DIR}/resource")
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
