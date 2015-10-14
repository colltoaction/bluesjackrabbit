#ifndef BLUESJACKRABBIT_HELLOWORLDTEST_H
#define BLUESJACKRABBIT_HELLOWORLDTEST_H

#include <cppunit/extensions/HelperMacros.h>

class HelloWorldTest : public CppUnit::TestFixture {
    CPPUNIT_TEST_SUITE( HelloWorldTest );
    CPPUNIT_TEST(testReturnsHelloWorld);
    CPPUNIT_TEST_SUITE_END();

public:
    void setUp();
    void tearDown();
    void testReturnsHelloWorld();
};

#endif //BLUESJACKRABBIT_HELLOWORLDTEST_H
