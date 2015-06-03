include(ExternalProject)
project("")
ExternalProject_Add(
    MATH3D
    GIT_REPOSITORY "https://github.com/MoriokaReimen/Math.git"
    GIT_TAG "master"
    PREFIX ${CMAKE_CURRENT_BINARY_DIR}/Math3D
    CMAKEARGS -DCMAKE_INSTALL_PREFIX:PATH=<INSTALL_DIR>)
