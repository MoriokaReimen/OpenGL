cmake_minimum_required(VERSION 2.8)
# include math3d
project(Math3D)
include(ExternalProject)
ExternalProject_Add(MATH3D
    PREFIX ${CMAKE_SOURCE_DIR}/external/Math3D
    GIT_REPOSITORY "https://github.com/MoriokaReimen/Math.git"
    GIT_TAG "master"
    INSTALL_DIR ${CMAKE_SOURCE_DIR}/external/Math3D
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_SOURCE_DIR}/external)

include_directories(${CMAKE_SOURCE_DIR}/external/include)
link_directories(${CMAKE_SOURCE_DIR}/external/lib)

add_subdirectory(OpenGL)
