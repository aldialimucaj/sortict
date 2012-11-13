//Sortit.h
/*
 * This file is part of the open source project Sortit.
 * LGPL Licence
 *
 * Aldi Alimucaj 2012
 *
 */
#ifndef _SORTERIT_
#define _SORTERIT_

#include <string>
#include <vector>
#include <boost/array.hpp>
#include <boost/assign.hpp>
#include <boost/smart_ptr.hpp>

#include "IOSorter.h"

#define SORTIT_REST_FOLDER "_REST"

using namespace std;
using namespace boost;



typedef multimap<string, string> file_set_t;

// This class represents a sorter object which is able to sort
// files based on different criteria.

class SortIt {



private:
    IOSorter m_iosorter;
    string m_srcPath;
    string m_dstPath;
    int m_treeDepth;
    bool m_noRest;
    std::vector<string> m_alphabet;// = {"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "REST", "_ZIP"};
    
    string getStructuredFolder(string folderName, int times);
    
    
public:
    
    SortIt();
    SortIt(string srcPath, string dstPath);
    SortIt(string srcPath, string dstPath, int _rDepth);
    ~SortIt();
    
    // ----------- Variables ---------------------------------------------------
    
    
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
    
    /**
     *  Deletes every empty folder of the structure.
     * 
     * @param dstPath path to the folder
     */
    void cleanStructure(const string dstPath);
    
    
    bool isRestFile(path filePath);
    
    
    // --------- File Manipulation ---------------------------------------------
    /**
     * Sorts the given list of items
     * @param vec Vector of paths containing multimedia files
     * 
     */
    void startSorting(file_set_t filesMap);
    
    file_set_t buildFileMap(vector<path> vec);

    //---------- Getter/Setter -------------------------------------------------
    void setDstPath(string _dstPath);
    string getDstPath() const;
    void setSrcPath(string _srcPath);
    string getSrcPath() const;
    void setTreeDepth(int treeDepth);
    int getTreeDepth() const;
    void setRest(bool rest);
    bool isRest() const;
};

#endif