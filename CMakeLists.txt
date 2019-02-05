cmake_minimum_required(VERSION 3.12)
set(CMAKE_CXX_STANDARD 17)

set(INSTALL_DIR ${CMAKE_HOME_DIRECTORY})
set(CMAKE_INSTALL_PREFIX ${INSTALL_DIR})

if(NOT DEFINED CMAKE_PREFIX_PATH)
    set(CMAKE_PREFIX_PATH ${INSTALL_DIR})
endif()

include(ExternalProject)
set(EP_BASE extern)

# All of the arguments to pass to external projects.
set(_CMAKE_ARGS
    CMAKE_INSTALL_PREFIX=${INSTALL_DIR}
    CMAKE_PREFIX_PATH=${CMAKE_PREFIX_PATH}
    )
list(TRANSFORM _CMAKE_ARGS PREPEND "-D")

ExternalProject_Add(lib-ck
    GIT_REPOSITORY https://github.com/concurrencykit/ck.git
    GIT_TAG 0.6.0
    GIT_SHALLOW TRUE
    INSTALL_DIR ${INSTALL_DIR}
    UPDATE_COMMAND ""
    PATCH_COMMAND ${CMAKE_HOME_DIRECTORY}/patch-ck.sh
    CONFIGURE_COMMAND <SOURCE_DIR>/configure --prefix=${INSTALL_DIR}
    BUILD_COMMAND make -j
    INSTALL_COMMAND make install
    STEP_TARGETS install
    )

ExternalProject_Add(lib-swoc++
    GIT_REPOSITORY https://github.com/solidwallofcode/libswoc.git
    GIT_TAG master
    GIT_SHALLOW TRUE
    SOURCE_SUBDIR swoc++
    INSTALL_DIR ${INSTALL_DIR}
    CMAKE_ARGS "${_CMAKE_ARGS}"
    STEP_TARGETS install
    )

ExternalProject_Add(demo
    SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/demo
    INSTALL_DIR ${INSTALL_DIR}
    CMAKE_ARGS "${_CMAKE_ARGS}"
    DEPENDS lib-ck-install lib-swoc++-install
    STEP_TARGETS install
    )

ExternalProject_Add(lib-ckpp
    SOURCE_DIR ${CMAKE_HOME_DIRECTORY}/demo
    INSTALL_DIR ${INSTALL_DIR}
    CMAKE_ARGS "${_CMAKE_ARGS}"
    DEPENDS lib-ck-install lib-swoc++-install
    STEP_TARGETS install
    )

# If using CLion, pass "-DENABLE_IDE_HACKS=TRUE" as a CMake argument to make the editor behave as desired.
if(${ENABLE_IDE_HACKS})
    add_custom_target(clang-format COMMAND ${CMAKE_HOME_DIRECTORY}/tools/clang-format.sh demo/src ckpp/src ckpp/include/ckpp)
    add_subdirectory(demo)
    add_subdirectory(ckpp)
endif()
