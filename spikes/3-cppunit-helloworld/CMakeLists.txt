cmake_minimum_required(VERSION 2.6)
project(3-cppunit-helloworld)

add_executable(${PROJECT_NAME}
    main_test.cpp HelloWorldTest.cpp HelloWorldTest.h HelloWorld.cpp HelloWorld.h)
target_link_libraries(${PROJECT_NAME} cppunit)

add_test(${PROJECT_NAME}-tests ${PROJECT_NAME})
