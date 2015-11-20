project(common)

set(SOURCES
        Configuration.cpp
        Configuration.h
        InvalidMessageException.cpp
        InvalidMessageException.h
        Lock.cpp
        Lock.h
        Logger.cpp
        Logger.h
        MessageReader.cpp
        MessageReader.h
        Mutex.cpp
        Mutex.h
        Socket.cpp
        Socket.h
        Thread.cpp
        Thread.h
)
include(CppLint)

add_library(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${LOG4CPP_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${CMAKE_THREAD_LIBS_INIT})
