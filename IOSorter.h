/**
 * \brief This class takes care of all io for the sorter.
 *
 *
 */
#ifndef _IOSORTER_
#define _IOSORTER_

#include <iostream>
#include <string>
#include <sstream>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>

#define MAX_DIR_RECURSION 3  // the maxiamal depth of the subdir structure

using namespace std;
using namespace boost::filesystem;

class IOSorter {
public:
    IOSorter();
    ~IOSorter();
    
    string getPath();
    bool isPathCorrect(const string path);
    void safeCreateFolder(const string path);
    vector<path> listFolder(path path);
    bool isMultimedia(const path path);
    
    vector<string> multimediaType;

};

#endif