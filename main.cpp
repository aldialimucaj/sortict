/* 
 * File:   main.cpp
 * Author: a
 *
 * Created on October 28, 2012, 12:42 AM
 */

#include <cstdlib>
#include <string>
#include "Sortit.h"
#include "IOSorter.h"

using namespace std;

/*
 * Main function for sortit 
 */
int main(int argc, char** argv) {

    Sortit sorter;
    IOSorter iosorter;

    string path = iosorter.getPath();
    sorter.sort(path);
    sorter.createStructure(path, 0);


    return 0;
}

