cmake_minimum_required(VERSION 2.6)

project(server)

set(SOURCES
        main.cpp
        ClientProxy.cpp
        ClientProxy.h
        ClientProxyAcceptor.cpp
        ClientProxyAcceptor.h
        Game.cpp
        Game.h
        GameMonitor.cpp
        GameMonitor.h
        GameRunner.cpp
        GameRunner.h
        Map.cpp
        Map.h
        Server.cpp
        Server.h
)
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/server.ini"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/server.ini" "${CMAKE_CURRENT_BINARY_DIR}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/server.ini"
        COMMENT "Copying server configuration \"server.ini\"")
add_custom_target(copy_server.ini DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/server.ini")
add_dependencies(${PROJECT_NAME} copy_server.ini)

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

add_dependencies(${PROJECT_NAME} engine)
add_dependencies(${PROJECT_NAME} common)

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} engine)
target_link_libraries(${PROJECT_NAME} common)
