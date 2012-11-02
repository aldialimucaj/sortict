#include <iostream>
#include <string>
#include <sstream>
#include <dirent.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include <map>
#include "IOSorter.h"


using namespace std;
using namespace boost::filesystem;

IOSorter::IOSorter(): multimediaType({".pdf"}) {
    
}

IOSorter::~IOSorter() {

}

string IOSorter::getPath() {
    string _path;

    cout << "Path to sort: " << endl;
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

        if (is_regular_file(_tmpPath) && isMultimedia(_tmpPath)) {
            vec.push_back(_tmpPath);
            //TODO: take this out
            //cout << (*di).path() << endl;
        }

    }

    return vec;

}

bool IOSorter::isMultimedia(const path _path) {
    string _strPath = _path.string();
    
    for (int i = 0; i < multimediaType.size(); i++) {
        if (_strPath.find_last_of(IOSorter::multimediaType.at(i)) > 0) {
            return true;
        }

    }
    return false;
}

bool IOSorter::isPathCorrect(const string dir_path) {
    path _path(dir_path);

    return is_directory(_path);

}
