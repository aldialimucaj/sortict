#include <iostream>
#include <string>
#include <sstream>
#include "Sortit.h"
#include "IOSorter.h"

using namespace std;

Sortit::Sortit(): iosorter()
{
    
}

void Sortit::sort(const string path)
{
    cout << "TEST: soriting path: " << path << endl;
    cout << "Path correct: " << iosorter.isPathCorrect(path) << endl;
}

void Sortit::sort()
{
	cout << "Yeah to be implemented ..." << endl;
}


	
