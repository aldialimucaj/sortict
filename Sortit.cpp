#include <iostream>
#include <string>
#include <sstream>
#include <exception>
#include <boost/filesystem/path.hpp>
#include <boost/foreach.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/numeric/conversion/converter.hpp>
#include <boost/assign.hpp>
#include "Sortit.h"
#include "IOSorter.h"

using namespace std;
using namespace boost::assign;

SortIt::SortIt() : SortIt(EMTPY_STRING, EMTPY_STRING, 0) {
}

SortIt::SortIt(string srcPath, string dstPath) : SortIt(srcPath, dstPath, 0) {
}

SortIt::SortIt(string srcPath, string dstPath, int _rDepth)
: m_srcPath(srcPath),
m_dstPath(dstPath),
m_treeDepth(_rDepth),
m_noRest(false),
m_statsFlag(false),
m_statDuplications(0),
m_alphabet({SORTIT_REST_FOLDER, "A", "B", "C", "D", "E", "F", "G", "H", "I", "J", "K", "L", "M", "N", "O", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z", "_ZIP"}) {
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
    vector<path> vec = m_iosorter.listFolder(m_srcPath);
    file_set_t filesMap = SortIt::buildFileMap(vec);
    SortIt::startSorting(filesMap);
    m_statMultiFiles = vec.size();
}

int SortIt::isCorrectFile(path file) {
    string fileName = file.filename().string();

    // EXISTS = -1
    if (!exists(file)) {
        return -1;
    }

    // DUPLICATE = 1
    if (boost::starts_with(fileName, DUPLICATE_FILE_TAG)) {
        return 1;
    }

    // FILE OK = 0
    return 0;
}

void SortIt::startSorting(file_set_t filesMap) {

    BOOST_FOREACH(file_set_t::value_type &m, filesMap) {
        // if source and destination are the same!
        if (m.first.compare(m.second) == 0) {
            continue;
        }

        path _fileToMove(m.first);
        path _destination(m.second);



        try {
            if (!exists(_destination) && isCorrectFile(_fileToMove) == 0) {
                m_iosorter.safeCreateFolders(_destination.parent_path().string());

                // RENAMING -- only if the stats flag is not set
                if (!isStatsFlag()) {
                    rename(_fileToMove, _destination);
                }

                cout << "MV: " << _fileToMove.string() << " >> " << _destination << endl;
                m_statFilesMoved++;
            } else if (exists(_fileToMove) == true) {

                if (isCorrectFile(_fileToMove) != 1) {
                    cout << "ERR (Exists): " << endl << _fileToMove.string() << endl << _destination.string() << endl << endl;
                    string _duplicateName = DUPLICATE_FILE_TAG + _fileToMove.filename().string();
                    path _duplicateFile(_fileToMove.parent_path().string() + "/" + _duplicateName);

                    // RENAMING -- only if the stats flag is not set
                    if (!isStatsFlag()) {
                        rename(_fileToMove, _duplicateFile);
                    }
                }
                m_statDuplications++;
            } else {
                cout << "ERR (Invalid path): " << _fileToMove.string() << " -> " << _destination.string() << endl;
            }
        } catch (filesystem_error &e) {
            cout << "Could not move File: " << _fileToMove.string() << " -> "
                    << _destination.string() << " MSG: " << e.what() << endl;
        }

    }
}

file_set_t SortIt::buildFileMap(vector<path> vec) {
    file_set_t fileSet;

    BOOST_FOREACH(path _filePath, vec) {
        if (SortIt::isRest()) {
            if (SortIt::isRestFile(_filePath)) {
                continue;
            }
        }

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

                correctFolderName.append(SortIt::getStructuredFolder(pathSufix, i));
                correctFolderName.append("/");
            }
            correctFolderName.append(fName);

            fileSet.insert(pair<string, string > (_filePath.string(), correctFolderName));
        }
    }
    return fileSet;
}

bool SortIt::isRestFile(path filePath) {
    string fileStr = filePath.filename().string();
    string result = SortIt::getStructuredFolder(fileStr.substr(0, 1), 1);

    if (result.empty()) {
        return true;
    }
    return false;
}

string SortIt::getStructuredFolder(string folderName, int times) {
    to_upper(folderName);

    BOOST_FOREACH(string alpha, m_alphabet) {
        if (folderName.compare(times - 1, 1, alpha) == 0) {
            if (times > 1) {
                return SortIt::getStructuredFolder(folderName.substr(0, times), times - 1) + alpha;
            }
            return alpha;
        }
    }
    if (times > 1) {
        return SortIt::getStructuredFolder(folderName.substr(0, times), times - 1) + SORTIT_REST_FOLDER;
    }

    // if NO-REST flag is set then return an empty string
    if (this->m_noRest) {
        return EMTPY_STRING;
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

    // Goes through the alphabet list and some special predefined folders
    // TODO: this list is static and has to be changed

    BOOST_FOREACH(string alpha, m_alphabet) {
        int _depth = 0;

        if (treeDepth < MAX_DIR_RECURSION && treeDepth > 0) {
            _depth = treeDepth;
        }

        string _recursion_dir_name = EMTPY_STRING;
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

void SortIt::cleanStructure(const string dstPath) {
    path _path(dstPath);

    recursive_directory_iterator di(_path);
    recursive_directory_iterator end_iter;

    for (di; di != end_iter; ++di) {
        path _tmpPath((*di).path());
        if (is_directory(_tmpPath) && boost::filesystem::is_empty(_tmpPath)) {
            remove(_tmpPath);
        }

    }
}

void SortIt::printStats() {
    cout << "************************************************" << endl;
    cout << "Overall multimedia files: " << m_statMultiFiles << endl;
    cout << "Files reallocated: " << m_statFilesMoved << endl;
    cout << "Duplications: " << m_statDuplications << endl;
    cout << "************************************************" << endl;
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

void SortIt::setTreeDepth(int treeDepth) {
    this->m_treeDepth = treeDepth;
}

int SortIt::getTreeDepth() const {
    return m_treeDepth;
}

void SortIt::setRest(bool rest) {
    this->m_noRest = rest;
}

bool SortIt::isRest() const {
    return m_noRest;
}

void SortIt::setStatsFlag(bool statsFlag) {
    this->m_statsFlag = statsFlag;
}

bool SortIt::isStatsFlag() const {
    return m_statsFlag;
}

void SortIt::setStatDuplications(int statDuplications) {
    this->m_statDuplications = statDuplications;
}

int SortIt::getStatDuplications() const {
    return m_statDuplications;
}

void SortIt::setStatFilesMoved(int statFilesMoved) {
    this->m_statFilesMoved = statFilesMoved;
}

int SortIt::getStatFilesMoved() const {
    return m_statFilesMoved;
}

void SortIt::setStatMultiFiles(int statMultiFiles) {
    this->m_statMultiFiles = statMultiFiles;
}

int SortIt::getStatMultiFiles() const {
    return m_statMultiFiles;
}

SortIt::~SortIt() {
}
