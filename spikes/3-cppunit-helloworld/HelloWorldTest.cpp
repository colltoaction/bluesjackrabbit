#include "HelloWorldTest.h"
#include "HelloWorld.h"

CPPUNIT_TEST_SUITE_REGISTRATION( HelloWorldTest );

void HelloWorldTest::setUp() {
}

void HelloWorldTest::tearDown() {
}

void HelloWorldTest::testReturnsHelloWorld() {
    std::string expected = "Hello World!";
    HelloWorld hw;
    CPPUNIT_ASSERT_EQUAL( expected, hw.getHW() );
}
