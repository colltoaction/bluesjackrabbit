cmake_minimum_required(VERSION 2.6)

find_package (Threads)
project(server)

set(SOURCES
        main.cpp
        ListenerSocket.cpp
        ListenerSocket.h
        Socket.cpp
        Socket.h
        Thread.cpp
        Thread.h
)
# include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)
add_dependencies(${PROJECT_NAME} engine)

target_link_libraries (${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
target_link_libraries(${PROJECT_NAME} engine)
directamente el codigo en el proyecto server, el problema es que la clase Engine usa una senial de glib para hacer el loop de iteracion
