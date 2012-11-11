/*
 * File:   TestSortit.cpp
 * Author: a
 *
 * Created on Oct 28, 2012, 11:08:51 PM
 */

#include "TestSortit.h"
#include "../Sortit.h"


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
    SortIt sortit();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(true);
    }
}

void TestSortit::testSort() {
    string path;
    SortIt sortit;
    sortit.sort(path);
    if (true /*check result*/) {
        CPPUNIT_ASSERT(true);
    }
}

void TestSortit::testSort2() {
    SortIt sortit;
    sortit.sort();
    if (true /*check result*/) {
        CPPUNIT_ASSERT(true);
    }
}

