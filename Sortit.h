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

typedef multimap<string, string> file_set_t;

// This class represents a sorter object which is able to sort
// files based on different criteria.

class Sortit {
private:
    IOSorter iosorter;
    string _srcPath;
    string _dstPath;
    vector<string> alphabet;
    int _treeDepth;
    
    
public:
    Sortit();
    Sortit(string srcPath, string dstPath);
    Sortit(string srcPath, string dstPath, int _rDepth);
    ~Sortit();
    // entry point for the sorting process.
    void sort();
    void sort(string srcPath);
    void sort(string srcPath, string dstPath);
    
    //----------- Folder Structure ---------------------------------------------
    /**
     * This method creates a substructure inside the destination folder.
     * Version 0.1 creates alphanumeric subfolders by a dictated depth.
     * 
     * @param srcPath
     * @param depth Depth of the folders structure. 0 is first level with A-Z.
     * If it is 1 then folder A for example gets subfolders named AA, AB and so on.
     */
    void createStructure(const string dstPath, const int depth, int rdepth);
    
    /**
     * See createStructure(const string dstPath, const int depth, int rdepth)
     * 
     * <b>int rdepth = 0</b>
     * 
     * @param dstPath
     * @param depth
     */
    void createStructure(const string dstPath, const int depth);
    
    
    // --------- File Manipulation ---------------------------------------------
    /**
     * Sorts the given list of items
     * @param vec Vector of paths containing multimedia files
     * 
     */
    void startSorting(vector<path> vec);
    
    file_set_t buildFileMap(vector<path> vec);

    //---------- Getter/Setter -------------------------------------------------
    void setDstPath(string _dstPath);
    string getDstPath() const;
    void setSrcPath(string _srcPath);
    string getSrcPath() const;
};
