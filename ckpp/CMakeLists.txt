cmake_minimum_required(VERSION 3.12)

project(ckpp CXX)
set(CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

find_package(swoc++ CONFIG REQUIRED)

add_library(ckpp STATIC
    src/CKHashMap.cc
)

target_include_directories(ckpp
    PUBLIC
    $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    )

target_link_libraries(ckpp PRIVATE ${CMAKE_INSTALL_PREFIX}/lib/libck.a)
target_link_libraries(ckpp PUBLIC swoc++::swoc++)

install(TARGETS ckpp
    EXPORT ckpp-config
    ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
    )
install(DIRECTORY include/ckpp DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})
install(EXPORT ckpp-config
    NAMESPACE ckpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ckpp
    )
#export(TARGETS ckpp FILE ckpp-config.cmake)
