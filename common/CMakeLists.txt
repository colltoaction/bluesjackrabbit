project(common)

set(SOURCES
        Configuration.cpp
        Configuration.h
        Constants.h
        CreateGameMessage.cpp
        CreateGameMessage.h
        GameInitMessage.cpp
        GameInitMessage.h
        GameObjectMessage.cpp
        GameObjectMessage.h
        GamesMessage.cpp
        GamesMessage.h
        InvalidMessageException.cpp
        InvalidMessageException.h
        JoinGameMessage.cpp
        JoinGameMessage.h
        Lock.cpp
        Lock.h
        Logger.cpp
        Logger.h
        LoggerScope.cpp
        LoggerScope.h
        MapsMessage.cpp
        MapsMessage.h
        Message.cpp
        Message.h
        MessageReader.cpp
        MessageReader.h
        MessageWriter.cpp
        MessageWriter.h
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
