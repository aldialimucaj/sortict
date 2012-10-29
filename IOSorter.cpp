#include <iostream>
#include <string>
#include <sstream>
#include <dirent.h>
#include <boost/filesystem.hpp>
#include <boost/filesystem/operations.hpp>
#include "IOSorter.h"


using namespace std;
using namespace boost::filesystem;

IOSorter::IOSorter() {

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
    
}

bool IOSorter::isPathCorrect(const string dir_path) {
    path _path(dir_path);

    return is_directory(_path);

}
