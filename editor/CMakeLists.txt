cmake_minimum_required(VERSION 2.6)
project(editor)


find_package(PkgConfig REQUIRED)
pkg_check_modules(CAIROMM REQUIRED cairomm-1.0)
pkg_check_modules(GTKMM3 REQUIRED gtkmm-3.0)
pkg_check_modules(GOOCANVAS REQUIRED goocanvas-2.0)
pkg_check_modules(LIBXML REQUIRED libxml++-2.6)

link_directories(${CAIROMM_LIBRARY_DIRS})
link_directories(${GTKMM3_LIBRARY_DIRS})
link_directories(${GOOCANVAS_LIBRARY_DIRS})
include_directories(SYSTEM ${CAIROMM_INCLUDE_DIRS})
include_directories(SYSTEM ${GTKMM3_INCLUDE_DIRS})
include_directories(SYSTEM ${GOOCANVAS_INCLUDE_DIRS})
include_directories(SYSTEM ${LIBXML_INCLUDE_DIRS})

set(SOURCES main.cpp
			EditorWindow.cpp
			EditorController.cpp
			EditorCanvas.cpp
			CustomToolButton.cpp
			CircleButton.cpp
			RectButton.cpp)

include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/assets/brown_nature.png"
        COMMAND ${CMAKE_COMMAND} -E copy "${CMAKE_CURRENT_SOURCE_DIR}/assets/brown_nature.png" "${CMAKE_CURRENT_BINARY_DIR}"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets/brown_nature.png"
        COMMENT "Copying asset files: brown_nature.png")
add_custom_target(copy_brown_nature.png DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/assets/brown_nature.png")
add_dependencies(${PROJECT_NAME} copy_brown_nature.png)

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${CAIROMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GOOCANVAS_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBXML_LIBRARIES})

file(COPY window.glade
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

