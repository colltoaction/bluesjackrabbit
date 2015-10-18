cmake_minimum_required(VERSION 2.6)
project(3-cppunit-helloworld)

set(SOURCES main_test.cpp HelloWorldTest.cpp HelloWorldTest.h HelloWorld.cpp HelloWorld.h)
include(CppLint)

add_executable(${PROJECT_NAME} ${SOURCES})
add_style_check_target(${PROJECT_NAME}-lint "${SOURCES}")
add_dependencies(${PROJECT_NAME} ${PROJECT_NAME}-lint)

target_link_libraries(${PROJECT_NAME} cppunit)

add_test(${PROJECT_NAME}-tests ${PROJECT_NAME})
