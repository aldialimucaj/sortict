#include <iostream>
#include <string>
#include <sstream>
#include "IOSorter.h"


using namespace std;


string IOSorter::getPath()
{
	string _path;
	
	cout << "Path to sort: " << endl;
	getline(cin, _path);
	
        return _path;
}
