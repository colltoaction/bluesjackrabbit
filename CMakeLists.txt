cmake_minimum_required(VERSION 2.6)
project(BluesJackrabbit)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/cmake_modules/")
find_package(cppunit REQUIRED)
enable_testing()
add_subdirectory(spikes)
