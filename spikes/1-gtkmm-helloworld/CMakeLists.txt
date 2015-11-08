cmake_minimum_required(VERSION 2.6)
project(1-gtkmm-helloworld)

link_directories(${GTKMM3_LIBRARY_DIRS})
include_directories(SYSTEM ${GTKMM3_INCLUDE_DIRS})

set(SOURCES main.cpp)
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
