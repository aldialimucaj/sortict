#include <iostream>
#include <string>
#include <sstream>
#include <boost/filesystem/path.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/assign.hpp>
#include "Sortit.h"
#include "IOSorter.h"

using namespace std;
using namespace boost::assign;

SortIt::SortIt() : SortIt("", "", 0) {
}

SortIt::SortIt(string srcPath, string dstPath) : SortIt(srcPath, dstPath, 0) {
}

SortIt::SortIt(string srcPath, string dstPath, int _rDepth)
: m_srcPath(srcPath),
m_dstPath(dstPath),
m_treeDepth(_rDepth),
m_alphabet({"A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "REST", "_ZIP"}) {
}

void SortIt::sort() {
    if (!m_iosorter.isPathCorrect(this->m_srcPath) || !m_iosorter.isPathCorrect(this->m_dstPath)) {
        return;
    }
    this->sort(this->m_srcPath, this->m_dstPath);
}

void SortIt::sort(const string srcPath) {
    if (!m_iosorter.isPathCorrect(srcPath)) {
        return;
    }
    this->sort(srcPath, srcPath);
}

void SortIt::sort(const string srcPath, const string dstPath) {
    if (!m_iosorter.isPathCorrect(srcPath) || !m_iosorter.isPathCorrect(dstPath)) {
        return;
    }
    vector<path> vec = m_iosorter.listFolder(m_dstPath);
    file_set_t filesMap = SortIt::buildFileMap(vec);
    SortIt::startSorting(filesMap);
}

void SortIt::startSorting(file_set_t filesMap) {

    BOOST_FOREACH(file_set_t::value_type &m, filesMap) {
        cout << m.first << " -> " << m.second << endl;
    }
}

file_set_t SortIt::buildFileMap(vector<path> vec) {
    file_set_t fileSet;

    BOOST_FOREACH(path _filePath, vec) {
        // _tmpDepth is the folder name which is going to be added to the path
        int _tmpDepth = this->m_treeDepth + 1;

        string fName = _filePath.filename().string();

        // the filename has to be longer than the depth otherwise one cannot crate a folder.
        // TODO: otherwise put it on the parent folder
        if (fName.size() >= _tmpDepth) {
            string _folderName = fName.substr(0, _tmpDepth);

            string correctFolderName;
            correctFolderName.assign(this->m_dstPath);

            int i = 0;
            correctFolderName.append("/");

            while (i < _tmpDepth) {
                string pathSufix = fName.substr(0, ++i);

                correctFolderName.append(SortIt::getSufix(pathSufix, i));
                correctFolderName.append("/");
            }
            correctFolderName.append(fName);

            fileSet.insert(pair<string, string > (_filePath.string(), correctFolderName));
        }
    }
    return fileSet;
}

string SortIt::getSufix(string folderName, int times) {

    BOOST_FOREACH(string alpha, m_alphabet) {
        if (folderName.compare(times-1, 1, alpha) == 0) {
            to_upper(folderName);
            return folderName;
        }
    }

    return SORTIT_REST_FOLDER;

}

void SortIt::createStructure(const string dstPath, const int treeDepth) {
    this->createStructure(dstPath, treeDepth, 0);
}

void SortIt::createStructure(const string dstPath, const int treeDepth, int rdepth) {
    if (!m_iosorter.isPathCorrect(dstPath)) {
        return;
    }

    int _depth = 0;

    if (treeDepth < MAX_DIR_RECURSION && treeDepth > 0) {
        _depth = treeDepth;
    }

    // Goes through the alphabet list and some special predefined folders
    // TODO: this list is static and has to be changed

    BOOST_FOREACH(string alpha, m_alphabet) {
        string _recursion_dir_name = "";
        if (rdepth > 0) {
            path _dstPath(dstPath);
            _recursion_dir_name = _dstPath.filename().string();
        }

        _recursion_dir_name.append(alpha);

        // building the path and crating the directory, only if it doesn't exist
        string _tmp_path = dstPath + "/" + _recursion_dir_name;
        m_iosorter.safeCreateFolder(_tmp_path);

        // starting recursion to create subdirectories
        if (treeDepth > 0) {
            SortIt::createStructure(_tmp_path, --_depth, rdepth + 1);
        }
    }


}

void SortIt::setDstPath(string _dstPath) {
    this->m_dstPath = _dstPath;
}

string SortIt::getDstPath() const {
    return m_dstPath;
}

void SortIt::setSrcPath(string _srcPath) {
    this->m_srcPath = _srcPath;
}

string SortIt::getSrcPath() const {
    return m_srcPath;
}

SortIt::~SortIt() {
}
