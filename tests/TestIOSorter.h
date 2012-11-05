/*
 * File:   TestIOSorter.h
 * Author: a
 *
 * Created on Oct 29, 2012, 1:12:31 AM
 */

#ifndef TESTIOSORTER_H
#define	TESTIOSORTER_H

#include <cppunit/extensions/HelperMacros.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

class TestIOSorter : public CPPUNIT_NS::TestFixture {
    CPPUNIT_TEST_SUITE(TestIOSorter);

    CPPUNIT_TEST(testIOSorter);
    CPPUNIT_TEST(testGetPath);
    CPPUNIT_TEST(testIsPathCorrect);
    CPPUNIT_TEST(testIsMultimedia);

    CPPUNIT_TEST_SUITE_END();

public:
    TestIOSorter();
    virtual ~TestIOSorter();
    void setUp();
    void tearDown();

private:
    void testIOSorter();
    void testGetPath();
    void testIsPathCorrect();
    void testIsMultimedia();

};

#endif	/* TESTIOSORTER_H */

