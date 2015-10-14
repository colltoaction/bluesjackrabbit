cmake_minimum_required(VERSION 2.6)
project(1-gtkmm-helloworld)
set(CMAKE_CXX_STANDARD 11)

# Use the package PkgConfig to detect GTK+ headers/library files
find_package(PkgConfig REQUIRED)
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)

# Setup CMake to use GTK+, tell the compiler where to look for headers
# and to the linker where to look for libraries
link_directories(${GTKMM3_LIBRARY_DIRS})
include_directories(${GTKMM3_INCLUDE_DIRS})

add_executable(${PROJECT_NAME}
    main.cpp)
target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
