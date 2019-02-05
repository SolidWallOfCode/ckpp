cmake_minimum_required(VERSION 3.12)

project(ck-demo)
set(CMAKE_CXX_STANDARD 17)
include(GNUInstallDirs)

find_package(swoc++ CONFIG REQUIRED)

add_executable(ck-demo
    src/demo.cc
)

target_link_libraries(ck-demo PUBLIC swoc++::swoc++ ${CMAKE_INSTALL_PREFIX}/lib/libck.a)

install(TARGETS ck-demo
    EXPORT ckpp-demo-config
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
    )
install(EXPORT ckpp-demo-config
    NAMESPACE ckpp::
    DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/ckpp-demo
    )
export(TARGETS ck-demo FILE ckpp-demo-config.cmake)
