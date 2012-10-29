//Sortit.h
/*
 * This file is part of the open source project Sortit.
 * LGPL Licence
 *
 * Aldi Alimucaj 2012
 *
 */

#include <string>
#include <boost/array.hpp>
#include <boost/assign.hpp>
#include "IOSorter.h"

using namespace std;
using namespace boost;

// This class represents a sorter object which is able to sort
// files based on different criteria.

class Sortit {
private:
    IOSorter iosorter;
    string _srcPath;
    string _dstPath;
    vector<string> alphabet;
    
    
public:
    Sortit();
    Sortit(string srcPath, string dstPath);
    ~Sortit();
    // entry point for the sorting process.
    void sort();
    void sort(string srcPath);
    void sort(string srcPath, string dstPath);
    
    // folder structure
    /**
     * This method creates a substructure inside the destination folder.
     * Version 0.1 creates alphanumeric subfolders by a dictated depth.
     * 
     * @param srcPath
     * @param depth Depth of the folders structure. 0 is first level with A-Z.
     * If it is 1 then folder A for example gets subfolders named AA, AB and so on.
     */
    void createStructure(string dstPath, int depth);

    void setDstPath(string _dstPath);
    string getDstPath() const;
    void setSrcPath(string _srcPath);
    string getSrcPath() const;
};
