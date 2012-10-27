/**
  * \brief This class takes care of all io for the sorter.
  *
  *
  */
#ifndef _IOSORTER_
#define _IOSORTER_

#include <iostream>
#include <string>
#include <sstream>

using namespace std;

class IOSorter
{
	public:
		string getPath();
                bool isPathCorrect(const string path);

};

#endif