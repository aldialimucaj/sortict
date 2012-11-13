#include <iostream>
#include <string>
#include <sstream>
#include <dirent.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/assign.hpp>
#include <map>
#include "IOSorter.h"


using namespace std;
using namespace boost::filesystem;
using namespace boost::algorithm;
using namespace boost::assign;

IOSorter::IOSorter() {
m_multimediaType += ".pdf", ".chm", ".epub", ".mobi",".djvu" ,".opf",".rtf", ".lit", ".lrf" ;

}

string IOSorter::getPath(string msg) {
    string _path;

    cout  << msg << ": " << endl;
    getline(cin, _path);

    return _path;
}

void IOSorter::safeCreateFolder(const string dirPath) {
    path _path(dirPath);

    if (!exists(_path)) {
        create_directory(_path);
    }
}

vector<path> IOSorter::listFolder(path _path) {
    vector<path> vec;

    if (!is_directory(_path) || is_regular(_path)) {
        return vec;
    }

    recursive_directory_iterator di(_path);
    recursive_directory_iterator end_iter;

    for (di; di != end_iter; ++di) {
        path _tmpPath((*di).path());

        if (is_regular_file(_tmpPath) && isMultimedia(_tmpPath.filename().string())) {
            vec.push_back(_tmpPath);
        }

    }
    return vec;
}

bool IOSorter::isMultimedia(const string _fileName) {
    string _strPath = _fileName;
    string _mType = "";

    BOOST_FOREACH(_mType, m_multimediaType) {
        to_lower(_strPath);
        if (_strPath.rfind(_mType) != string::npos) {
            return true;
        }

    }
    return false;
}

bool IOSorter::isPathCorrect(const string dir_path) {
    path _path(dir_path);

    return is_directory(_path);

}


IOSorter::~IOSorter() {

}
