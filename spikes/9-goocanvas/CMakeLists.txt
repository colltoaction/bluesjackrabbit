cmake_minimum_required(VERSION 2.6)
project(9-goocanvas)

link_directories(${GTKMM3_LIBRARY_DIRS})
link_directories(${GOOCANVAS_LIBRARY_DIRS})
include_directories(SYSTEM ${GTKMM3_INCLUDE_DIRS})
include_directories(SYSTEM ${GOOCANVAS_INCLUDE_DIRS})

set(SOURCES main.cpp window.cpp window.h page.h primitives.cpp primitives.h)


add_executable(${PROJECT_NAME} ${SOURCES})
add_custom_target(${PROJECT_NAME}-static-files ALL DEPENDS ${STATIC_FILES}
        COMMENT "Copying static files")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-static-files)

target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
