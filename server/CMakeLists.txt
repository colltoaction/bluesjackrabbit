cmake_minimum_required(VERSION 2.6)

project(server)

set(SOURCES
        ClientProxy.cpp
        ClientProxy.h
        ClientProxyAcceptor.cpp
        ClientProxyAcceptor.h
        Constants.h
        Lock.cpp
        Lock.h
        Mutex.cpp
        Mutex.h
        Server.cpp
        Server.h
        Socket.cpp
        Socket.h
        Thread.cpp
        Thread.h
        main.cpp
)
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)
add_dependencies(${PROJECT_NAME} engine)

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} engine)
