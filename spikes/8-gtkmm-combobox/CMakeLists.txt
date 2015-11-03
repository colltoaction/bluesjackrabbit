cmake_minimum_required(VERSION 2.6)
project(8-gtkmm-combobox)

set(SOURCES main.cpp examplewindow.cpp examplewindow.h)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_custom_target(${PROJECT_NAME}-static-files ALL DEPENDS ${STATIC_FILES}
        COMMENT "Copying static files")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint ${PROJECT_NAME}-static-files)

target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
