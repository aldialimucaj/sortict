#include <iostream>
#include <string>
#include <sstream>
#include <dirent.h>
#include "IOSorter.h"


using namespace std;


string IOSorter::getPath()
{
	string _path;
	
	cout << "Path to sort: " << endl;
	getline(cin, _path);
	
        return _path;
}

bool IOSorter::isPathCorrect(const string path)
{
    char* s = const_cast<char*>(path.c_str());
    if (opendir(s) != NULL){
        return true;
    }
    
    return false;
    
}
