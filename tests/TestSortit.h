/*
 * File:   TestSortit.h
 * Author: a
 *
 * Created on Oct 28, 2012, 11:08:51 PM
 */

#ifndef TESTSORTIT_H
#define	TESTSORTIT_H

#include <cppunit/extensions/HelperMacros.h>

class TestSortit : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(TestSortit);

    CPPUNIT_TEST(testSortit);
    CPPUNIT_TEST(testSort);
    CPPUNIT_TEST(testSort2);

    CPPUNIT_TEST_SUITE_END();

public:
    TestSortit();
    virtual ~TestSortit();
    void setUp();
    void tearDown();

private:
    void testSortit();
    void testSort();
    void testSort2();

};

#endif	/* TESTSORTIT_H */

