cmake_minimum_required(VERSION 3.26)
project(RouterSimulator)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})

find_package(Freetype REQUIRED)
include_directories(${FREETYPE_INCLUDE_DIRS})

add_subdirectory(librouter)
set(GENERATE_EXAMPLE_PROGRAM off)
include_directories(librouter/src)

include_directories(src)

add_executable(RouterSimulator main.cpp
        src/MainWindow.h
        src/MainWindow.cpp
        src/RouterContainer.cpp
        src/RouterContainer.h
        src/RouterPaned.cpp
        src/RouterPaned.h
        src/RouterInfo.cpp
        src/RouterInfo.h
        src/RouterActions.cpp
        src/RouterActions.h
        src/RouterToolBar.cpp
        src/RouterToolBar.h
        src/Actions/RouterActionAdd.cpp
        src/Actions/RouterActionAdd.h
        src/Actions/RouterActionErase.cpp
        src/Actions/RouterActionErase.h
)

target_link_libraries(RouterSimulator ${GTKMM_LIBRARIES} ${FREETYPE_LIBRARIES} librouter)