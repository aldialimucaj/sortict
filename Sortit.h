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
#include <boost/timer/timer.hpp>

#include "IOSorter.h"

#define SORTIT_REST_FOLDER "_REST"
#define DUPLICATE_FILE_TAG "DUP_"
#define EMTPY_STRING ""


using namespace std;
using namespace boost;
using namespace boost::timer;



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
    //---- stats ----
    int m_statMultiFiles;
    int m_statFilesMoved;
    int m_statDuplications;
    bool m_statsFlag;
    
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
    
    /**
     * Helps defining the nature of the file. Whether it is a duplicate file f.e.
     * 
     * -1 = file does not exist <br>
     * 0 = file is OK <br>
     * 1 = file is a duplicate. it starts with DUP_
     * 
     * @param file file to be checked. usually the source file
     * @return 
     */
    int isCorrectFile(path file);
    
    
    /**
     * Removes unsupported characters from the filename
     * 
     * @param file path of the file to be cleaned up
     */
    path cleanUpFileName(path file);
    
    
    // ------------------- Utils -----------------------------------------------
    void printStats(cpu_timer &timer);

    //---------- Getter/Setter -------------------------------------------------
    void setDstPath(string _dstPath);
    string getDstPath() const;
    void setSrcPath(string _srcPath);
    string getSrcPath() const;
    void setTreeDepth(int treeDepth);
    int getTreeDepth() const;
    void setRest(bool rest);
    bool isRest() const;
    void setStatsFlag(bool statsFlag);
    bool isStatsFlag() const;
    void setStatDuplications(int statDuplications);
    int getStatDuplications() const;
    void setStatFilesMoved(int statFilesMoved);
    int getStatFilesMoved() const;
    void setStatMultiFiles(int statMultiFiles);
    int getStatMultiFiles() const;
};

#endif