/* 
 * File:   main.cpp
 * Author: a
 *
 * Created on October 28, 2012, 12:42 AM
 */

#include <cstdlib>
#include <string>
#include <boost/filesystem.hpp>
#include "Sortit.h"
#include "IOSorter.h"

using namespace std;

/*
 * Main function for sortit 
 */
int main(int argc, char** argv) {

    Sortit sorter;
    IOSorter iosorter;

    string _dstPath = iosorter.getPath("Destination Path");
    string _srcPath = iosorter.getPath("Destination Path");
    
    sorter.sort(_dstPath);
    sorter.createStructure(_dstPath, 2);
    vector<path> vec = iosorter.listFolder(_dstPath);
    sorter.startSorting(vec);


    return 0;
}

