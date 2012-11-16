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

    // ----------- Variables ---------------------------------------------------
    vector<string> m_multimediaType;

    // ----------- Functions ---------------------------------------------------
    void safeCreateFolder(const string path);
    void safeCreateFolders(const string path);
    void safeDeleteFolder(const string path);
    string getPath(string msg);
    bool isPathCorrect(const string path);
    bool isMultimedia(const string _fileName);
    vector<path> listFolder(path path);




};

#endif