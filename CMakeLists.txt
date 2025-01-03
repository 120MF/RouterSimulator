cmake_minimum_required(VERSION 3.26)
project(RouterSimulator)

set(CMAKE_CXX_STANDARD 20)

find_package(PkgConfig)
pkg_check_modules(GTKMM gtkmm-4.0)
link_directories(${GTKMM_LIBRARY_DIRS})
include_directories(${GTKMM_INCLUDE_DIRS})


set(GENERATE_EXAMPLE_PROGRAM OFF)
set(GENERATE_BENCHMARK_TEST OFF)
set(GENERATE_CORRECTNESS_TEST OFF)
add_subdirectory(librouter)
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
        src/Actions/RouterActionConnect.cpp
        src/Actions/RouterActionConnect.h
        src/RouterNodeGraphTemplateImpl.cpp
        src/Actions/RouterActionShowShortestPath.cpp
        src/Actions/RouterActionShowShortestPath.h
)

target_link_libraries(RouterSimulator ${GTKMM_LIBRARIES} librouter)