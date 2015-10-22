cmake_minimum_required(VERSION 2.6)
project(client)

find_package (Threads)
find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)

link_directories(${CAIROMM_LIBRARY_DIRS})
link_directories(${GTKMM3_LIBRARY_DIRS})
include_directories(SYSTEM ${CAIROMM_INCLUDE_DIRS})
include_directories(SYSTEM ${GTKMM3_INCLUDE_DIRS})

set(SOURCES main.cpp
        Clickeable.h
        Event.cpp
        Event.h
        EventBus.cpp
        EventBus.h
        GameObject.cpp
        GameObject.h
        InitialScreen.cpp
        InitialScreen.h
        MainWindow.cpp
        MainWindow.h
        Point.cpp
        Point.h
        Renderer.cpp
        Renderer.h
        SceneRenderer.cpp
        SceneRenderer.h
        ServerProxy.cpp
        ServerProxy.h
        Stopwatch.cpp
        Stopwatch.h
        Transform.cpp
        Transform.h
        )
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

file(COPY main_frame.glade
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY new_game.glade
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${CAIROMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})