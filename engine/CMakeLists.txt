cmake_minimum_required(VERSION 2.6)
project(engine)

#link_directories(${SIGC_LIBRARY_DIRS})
#include_directories(SYSTEM ${SIGC_INCLUDE_DIRS})
#include_directories(SYSTEM ${GLIBMM_INCLUDE_DIRS})

set(SOURCES
        Engine.cpp
        Engine.h
        GameObject.cpp
        GameObject.h
        RigidBody.cpp
        RigidBody.h
        Transform.cpp
        Transform.h
        Vector.cpp
        Vector.h
)
include(CppLint)

add_library(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${SIGC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLIBMM_LIBRARIES})
