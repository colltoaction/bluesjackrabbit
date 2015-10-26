cmake_minimum_required(VERSION 2.6)
project(6-gtkmm-css)

link_directories(${GTKMM3_LIBRARY_DIRS})
include_directories(SYSTEM ${GTKMM3_INCLUDE_DIRS})

set(SOURCES main.cpp)
set(STATIC_FILES jazz.css Jazz.png)
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_custom_target(${PROJECT_NAME}-static-files ALL DEPENDS ${STATIC_FILES}
        COMMENT "Copying static files")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint ${PROJECT_NAME}-static-files)

file(COPY ${STATIC_FILES}
        DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
