cmake_minimum_required(VERSION 2.6)
project(engine)

set(SOURCES
        Body.h
        CircleCollider.cpp
        CircleCollider.h
        Collider.cpp
        Collider.h
        Engine.cpp
        Engine.h
        GameObject.cpp
        GameObject.h
        GameObjectBullet.cpp
        GameObjectBullet.h
        GameObjectPlayer.cpp
        GameObjectPlayer.h
        RectangleCollider.cpp
        RectangleCollider.h
        RigidBody.cpp
        RigidBody.h
        StaticBody.cpp
        StaticBody.h
        Vector.cpp
        Vector.h
)

add_library(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${SIGC_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GLIBMM_LIBRARIES})
