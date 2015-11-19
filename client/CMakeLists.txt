project(client)

set(SOURCES
        main.cpp
        BulletRenderer.cpp
        BulletRenderer.h
        CharacterRenderer.cpp
        CharacterRenderer.h
        Constants.h
        Event.cpp
        Event.h
        EventBus.cpp
        EventBus.h
        FloorRenderer.cpp
        FloorRenderer.h
        LocalServerProxy.cpp
        LocalServerProxy.h
        MainWindow.cpp
        MainWindow.h
        OtherCharacterRenderer.cpp
        OtherCharacterRenderer.h
        RemoteServerProxy.cpp
        RemoteServerProxy.h
        RemoteServerProxyUpdater.cpp
        RemoteServerProxyUpdater.h
        Renderer.cpp
        Renderer.h
        SceneRenderer.cpp
        SceneRenderer.h
        ServerProxy.h
        Stopwatch.cpp
        Stopwatch.h
        TurtleRenderer.cpp
        TurtleRenderer.h
)
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)
add_dependencies(${PROJECT_NAME} engine)
add_dependencies(${PROJECT_NAME} common)

target_link_libraries(${PROJECT_NAME} ${CAIROMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} engine)
target_link_libraries(${PROJECT_NAME} common)

file(COPY static
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
