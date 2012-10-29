/*
 * File:   TestIOSorter.cpp
 * Author: a
 *
 * Created on Oct 29, 2012, 1:12:32 AM
 */

#include "TestIOSorter.h"
#include "IOSorter.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestIOSorter);

TestIOSorter::TestIOSorter() {
}

TestIOSorter::~TestIOSorter() {
}

void TestIOSorter::setUp() {
}

void TestIOSorter::tearDown() {
}

void TestIOSorter::testIOSorter() {
    IOSorter iOSorter();
    if (iOSorter != NULL) {
        CPPUNIT_ASSERT(true);
    }
}

void TestIOSorter::testGetPath() {
    CPPUNIT_ASSERT(true);
}

void TestIOSorter::testIsPathCorrect() {
    IOSorter iOSorter;
    string t_path;
    bool result;
    
    t_path = "/home";
    result = iOSorter.isPathCorrect(t_path);
    CPPUNIT_ASSERT_EQUAL(result, true);
    
    t_path = "/bin";
    result = iOSorter.isPathCorrect(t_path);
    CPPUNIT_ASSERT_EQUAL(result, true);
    
    t_path = "/usr";
    result = iOSorter.isPathCorrect(t_path);
    CPPUNIT_ASSERT_EQUAL(result, true);
    
    t_path = "/lib";
    result = iOSorter.isPathCorrect(t_path);
    CPPUNIT_ASSERT_EQUAL(result, true);
    
    t_path = "/iCantBeADirectory";
    result = iOSorter.isPathCorrect(t_path);
    CPPUNIT_ASSERT_EQUAL(result, false);
    
    t_path = "NoriCantBeADirectory";
    result = iOSorter.isPathCorrect(t_path);
    CPPUNIT_ASSERT_EQUAL(result, false);
    
    t_path = "=/root";
    result = iOSorter.isPathCorrect(t_path);
    CPPUNIT_ASSERT_EQUAL(result, false);
    
    
}

