cmake_minimum_required(VERSION 2.6)
project(client)

find_package (Threads)

set(SOURCES
        main.cpp
        Constants.h
        CharacterRenderer.cpp
        CharacterRenderer.h
        Event.cpp
        Event.h
        EventBus.cpp
        EventBus.h
        GameObjectProxy.cpp
        GameObjectProxy.h
        LocalServerProxy.cpp
        LocalServerProxy.h
        Lock.cpp
        Lock.h
        MainWindow.cpp
        MainWindow.h
        Mutex.cpp
        Mutex.h
        RemoteServerProxy.cpp
        RemoteServerProxy.h
        Renderer.cpp
        Renderer.h
        SceneRenderer.cpp
        SceneRenderer.h
        ServerProxy.h
        Socket.cpp
        Socket.h
        Stopwatch.cpp
        Stopwatch.h
        Thread.cpp
        Thread.h
)
# include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
# add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)
add_dependencies(${PROJECT_NAME} engine)

target_link_libraries(${PROJECT_NAME} ${CAIROMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
target_link_libraries (client ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} engine)

file(COPY static/main_frame.glade
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY static/new_game.glade
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
file(COPY static/join_game.glade
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
