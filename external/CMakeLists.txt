include(ExternalProject)
project("")
ExternalProject_Add(
    MATH3D
    GIT_REPOSITORY "https://github.com/MoriokaReimen/Math.git"
    GIT_TAG "master"
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Math3D)
