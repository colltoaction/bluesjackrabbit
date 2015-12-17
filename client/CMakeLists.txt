project(client)

set(SOURCES
        main.cpp
        BulletRenderer.cpp
        BulletRenderer.h
        CharacterRenderer.cpp
        CharacterRenderer.h
        Event.cpp
        Event.h
        EventBus.cpp
        EventBus.h
        FloorRenderer.cpp
        FloorRenderer.h
        GreenTurtleRenderer.cpp
        GreenTurtleRenderer.h
        LivesRenderer.cpp
        LivesRenderer.h
        MainWindow.cpp
        MainWindow.h
        MeCharacterRenderer.cpp
        MeCharacterRenderer.h
        NewLifeRenderer.cpp
        NewLifeRenderer.h
        OtherCharacterRenderer.cpp
        OtherCharacterRenderer.h
        RedTurtleRenderer.cpp
        RedTurtleRenderer.h
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

add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/client.ini"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/client.ini" "${CMAKE_CURRENT_BINARY_DIR}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/client.ini"
        COMMENT "Copying client configuration \"client.ini\"")
add_custom_target(copy_client.ini DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/client.ini")
add_dependencies(${PROJECT_NAME} copy_client.ini)

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
