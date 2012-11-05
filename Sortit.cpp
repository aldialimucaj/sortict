#include <iostream>
#include <string>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include <boost/foreach.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include "Sortit.h"
#include "IOSorter.h"

using namespace std;

Sortit::Sortit() : _srcPath(), _dstPath(), _treeDepth(0) {
    Sortit(_srcPath, _dstPath, _treeDepth);
}

Sortit::Sortit(string srcPath, string dstPath)
: _srcPath(srcPath), _dstPath(dstPath) {
    Sortit(_srcPath, _dstPath, 0);
}

Sortit::Sortit(string srcPath, string dstPath, int _rDepth)
: iosorter(),
alphabet({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "REST", "_ZIP"}) {
    if (this->_dstPath.size() == 0) {
        this->_dstPath = iosorter.getPath("Destination Path");
    }
    if (this->_srcPath.size() == 0) {
        this->_srcPath = iosorter.getPath("Source Path");
    }
    if (this->_treeDepth == -1) {
        cout << "Structure depth [0-2]" << endl;
        cin >> this->_treeDepth;
    }


}

Sortit::~Sortit() {
}

void Sortit::sort() {
    if (!iosorter.isPathCorrect(this->_srcPath) || !iosorter.isPathCorrect(this->_dstPath)) {
        return;
    }
    this->sort(this->_srcPath, this->_dstPath);
}

void Sortit::sort(const string srcPath) {
    if (!iosorter.isPathCorrect(srcPath)) {
        return;
    }
    this->sort(srcPath, srcPath);
}

void Sortit::sort(const string srcPath, const string dstPath) {
    if (!iosorter.isPathCorrect(srcPath) || !iosorter.isPathCorrect(dstPath)) {
        return;
    }
}

void Sortit::startSorting(vector<path> vec) {

    BOOST_FOREACH(path _path, vec) {
        cout << _path << endl;
    }
}

//TODO: find a fucking map
file_set_t Sortit::buildFileMap(vector<path> vec) {
    file_set_t fileSet;

    BOOST_FOREACH(path _filePath, vec) {
        int _tmpDepth = this->_treeDepth + 1;
        string fName = _filePath.filename().string();
        if (fName.size() >= _tmpDepth) {
            string _folderName = fName.substr(0, _tmpDepth);
            string correctFolderName;
            correctFolderName.assign(this->_dstPath);
            int i = 1;
            correctFolderName.append("/");

            while (i < _tmpDepth) {
                correctFolderName.append(fName.substr(0, i++));
                correctFolderName.append("/");
            }
            correctFolderName.append(fName);
  
            fileSet.insert(pair<string,string>(_filePath.string(), correctFolderName));
        }
    }
    return fileSet;
}

void Sortit::createStructure(const string dstPath, const int treeDepth) {
    this->createStructure(dstPath, treeDepth, 0);
}

void Sortit::createStructure(const string dstPath, const int treeDepth, int rdepth) {
    if (!iosorter.isPathCorrect(dstPath)) {
        return;
    }

    int _depth = 0;

    if (treeDepth < MAX_DIR_RECURSION && treeDepth > 0) {
        _depth = treeDepth;
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
        if (treeDepth > 0) {
            Sortit::createStructure(_tmp_path, --_depth, rdepth + 1);
        }
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




