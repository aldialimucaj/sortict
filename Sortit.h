//Sortit.h
/*
 * This file is part of the open source project Sortit.
 * LGPL Licence
 *
 * Aldi Alimucaj 2012
 *
 */

#include <string>
#include "IOSorter.h"

using namespace std;

// This class represents a sorter object which is able to sort
// files based on different criteria.

class Sortit {
private:
    IOSorter iosorter;
    bool dirExists(string path);

public:
    Sortit();
    ~Sortit();
    // entry point for the sorting process.
    void sort();
    void sort(string path);
};
