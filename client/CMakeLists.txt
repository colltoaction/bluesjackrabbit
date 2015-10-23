cmake_minimum_required(VERSION 2.6)
project(client)

set(SOURCES
        main.cpp
        Event.cpp
        Event.h
        EventBus.cpp
        EventBus.h
        GameObjectProxy.cpp
        GameObjectProxy.h
        MainWindow.cpp
        MainWindow.h
        Renderer.cpp
        Renderer.h
        SceneRenderer.cpp
        SceneRenderer.h
        ServerProxy.cpp
        ServerProxy.h
        Stopwatch.cpp
        Stopwatch.h
)
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)
add_dependencies(${PROJECT_NAME} engine)

target_link_libraries(${PROJECT_NAME} ${CAIROMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} engine)

file(COPY main_frame.glade
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY new_game.glade
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
