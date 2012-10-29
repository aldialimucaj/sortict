#include <iostream>
#include <string>
#include <sstream>
#include "Sortit.h"
#include "IOSorter.h"

using namespace std;

Sortit::Sortit() : iosorter(),
    alphabet({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "REST", "_ZIP"})
{
    
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

void Sortit::createStructure(string dstPath, int depth) {
    if (!iosorter.isPathCorrect(dstPath)) {
        return;
    }

    for (int i = 0; i < Sortit::alphabet.size(); i++) {
        string _tmp_path = dstPath + "/" + Sortit::alphabet.at(i);
        iosorter.secureCreateFolder(_tmp_path);
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



