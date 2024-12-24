cmake_minimum_required(VERSION 3.26)
project(RouterSimulator)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig)

pkg_check_modules(GTKMM gtkmm-4.0)

include_directories(src)

link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_executable(RouterSimulator main.cpp
        src/helloworld.h
        src/helloworld.cpp)

target_link_libraries(RouterSimulator ${GTKMM_LIBRARIES})