include(ExternalProject)
project("")
ExternalProject_Add(MATH3D
    PREFIX ${CMAKE_CURRENT_LIST_DIR}/Math3D
    GIT_REPOSITORY "https://github.com/MoriokaReimen/Math.git"
    GIT_TAG "master"
    INSTALL_DIR ${CMAKE_CURRENT_LIST_DIR}/Math3D
    CMAKE_ARGS -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_LIST_DIR}/Math3D)
