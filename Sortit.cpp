#include <iostream>
#include <string>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include "Sortit.h"
#include "IOSorter.h"

using namespace std;

Sortit::Sortit() : iosorter(),
alphabet({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "REST", "_ZIP"}) {

}

Sortit::Sortit(string srcPath, string dstPath)
: iosorter(), _srcPath(srcPath), _dstPath(dstPath) {
    Sortit();
}

Sortit::~Sortit() {


}

void Sortit::sort(const string srcPath, const string dstPath) {
    if (!iosorter.isPathCorrect(srcPath) || !iosorter.isPathCorrect(dstPath)) {
        return;
    }


}

void Sortit::createStructure(const string dstPath, const int depth, int rdepth) {
    if (!iosorter.isPathCorrect(dstPath)) {
        return;
    }

    int _depth = 0;

    if (depth < MAX_DIR_RECURSION && depth > 0) {
        _depth = depth;
    }

    for (int i = 0; i < Sortit::alphabet.size(); i++) {
        string _recursion_dir_name = "";
        if (rdepth > 0) {
            path _dstPath(dstPath);
            _recursion_dir_name = _dstPath.filename().string();
        }

        _recursion_dir_name.append(Sortit::alphabet.at(i));

        // building the path and crating the directory, only if it doesn't exist
        string _tmp_path = dstPath + "/" + _recursion_dir_name;
        iosorter.safeCreateFolder(_tmp_path);

        // starting recursion to create subdirectories
        if (depth > 0) {
            Sortit::createStructure(_tmp_path, --_depth, rdepth + 1);
        }
    }


}

void Sortit::sort(const string srcPath) {
    if (!iosorter.isPathCorrect(srcPath)) {
        return;
    }
}

void Sortit::setDstPath(string _dstPath) {
    this->_dstPath = _dstPath;
}

string Sortit::getDstPath() const {
    return _dstPath;
}

void Sortit::setSrcPath(string _srcPath) {
    this->_srcPath = _srcPath;
}

string Sortit::getSrcPath() const {
    return _srcPath;
}

void Sortit::sort() {
    cout << "Yeah to be implemented ..." << endl;
}



