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
  src/Object.cpp include/Object.hpp
  src/ObjectUtil.cpp include/ObjectUtil.hpp
  src/Texture.cpp include/Texture.hpp
  src/GLFW.cpp include/GLFW.hpp
  src/BulletGLFW.cpp include/BulletGLFW.hpp
  include/BulletObject.hpp)
  # src/BulletObject.cpp include/BulletObject.hpp)
target_link_libraries(OpenGLTest
  pthread stdc++
  GLU GL X11 SOIL glfw GLEW
  BulletDynamics BulletCollision LinearMath)
