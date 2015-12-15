cmake_minimum_required(VERSION 2.6)
project(editor)

link_directories(${CAIROMM_LIBRARY_DIRS})
link_directories(${GTKMM3_LIBRARY_DIRS})
link_directories(${GOOCANVAS_LIBRARY_DIRS})
include_directories(SYSTEM ${CAIROMM_INCLUDE_DIRS})
include_directories(SYSTEM ${GTKMM3_INCLUDE_DIRS})
include_directories(SYSTEM ${GOOCANVAS_INCLUDE_DIRS})
include_directories(SYSTEM ${LIBXML_INCLUDE_DIRS})

set(SOURCES main.cpp
			BreakableRectButton.cpp
			BreakableRectItem.cpp
			CircleButton.cpp
			CircleItem.cpp
			CircleLevelObject.cpp
			ControlItem.cpp
			ControlToolButton.cpp
			CustomToolButton.cpp
			EditorCanvas.cpp
			EditorController.cpp
			EditorWindow.cpp
			GoalButton.cpp
			GoalItem.cpp
			GoalLevelObject.cpp
			GenericImageLevelObject.cpp
			ImageItem.cpp
			Level.cpp
			LevelLoader.cpp
			LevelObject.cpp
			LevelWriter.cpp
			Map.cpp
			RectButton.cpp
			RectItem.cpp
			RectangleLevelObject.cpp
			SpawnPointButton.cpp
			SpawnPointItem.cpp
			SpawnPointLevelObject.cpp
			StartPointButton.cpp
			StartPointItem.cpp
			StartPointLevelObject.cpp)

include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})

add_custom_command(
        OUTPUT "${CMAKE_CURRENT_BINARY_DIR}/assets"
        COMMAND ${CMAKE_COMMAND} -E copy_directory "${CMAKE_CURRENT_SOURCE_DIR}/assets" "${CMAKE_CURRENT_BINARY_DIR}/assets"
        DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/assets"
        COMMENT "Copying asset files")
add_custom_target(copy_assets DEPENDS "${CMAKE_CURRENT_BINARY_DIR}/assets")
add_dependencies(${PROJECT_NAME} copy_assets)

add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} ${CAIROMM_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GTKMM3_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${GOOCANVAS_LIBRARIES})
target_link_libraries(${PROJECT_NAME} ${LIBXML_LIBRARIES})

file(COPY window.glade
    DESTINATION ${CMAKE_CURRENT_BINARY_DIR})
