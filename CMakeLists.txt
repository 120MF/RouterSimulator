cmake_minimum_required(VERSION 3.26)
project(RouterSimulator)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

add_subdirectory(librouter)
set(GENERATE_EXAMPLE_PROGRAM off)
include_directories(librouter/src)

include_directories(src)

add_executable(RouterSimulator main.cpp
        src/helloworld.h
        src/helloworld.cpp)

target_link_libraries(RouterSimulator ${GTKMM_LIBRARIES} librouter)