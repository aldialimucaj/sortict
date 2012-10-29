/*
 * File:   TestSortit.cpp
 * Author: a
 *
 * Created on Oct 28, 2012, 11:08:51 PM
 */

#include "TestSortit.h"
#include "Sortit.h"


CPPUNIT_TEST_SUITE_REGISTRATION(TestSortit);

TestSortit::TestSortit() {
}

TestSortit::~TestSortit() {
}

void TestSortit::setUp() {
}

void TestSortit::tearDown() {
}

void TestSortit::testSortit() {
    Sortit sortit();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void TestSortit::testSort() {
    string path;
    Sortit sortit;
    sortit.sort(path);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

void TestSortit::testSort2() {
    Sortit sortit;
    sortit.sort();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(false);
    }
}

