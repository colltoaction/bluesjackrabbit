cmake_minimum_required(VERSION 2.6)
project(2-gtkmm-glade)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
link_directories(${GTKMM3_LIBRARY_DIRS})
include_directories(SYSTEM ${GTKMM3_INCLUDE_DIRS})

set(SOURCES main.cpp)
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint ${SOURCES})
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

file(COPY basic.glade
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
