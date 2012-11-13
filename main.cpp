/* 
 * File:   main.cpp
 * Author: a
 *
 * Created on October 28, 2012, 12:42 AM
 */

#include <cstdlib>
#include <string>
#include <boost/filesystem.hpp>
#include <boost/program_options.hpp>
#include "Sortit.h"
#include "IOSorter.h"

using namespace std;
using namespace boost::program_options;



/*
 * Main function for sortit 
 */
int main(int argc, char** argv) {
    SortIt sorter;
    IOSorter iosorter;
    string _dstPath;
    string _srcPath;
    int _interleave;


    options_description desc("Option List");

    desc.add_options()
            ("help", "Print this page")
            ("source,s", value<string > (), "Source Folder(s) where to look for the media data")
            ("destination,d", value<string > (), "Destination Folder where to reallocate the files. If no destination is set, the source folder will be set as destination")
            ("interleave,i", value<int>(), "the amount of sub-folder to create within the sorted folder. Example --interleave=1 would generate a structure like $DEST_FOLDER/A/AA")
            ("no-rest,n", "Don't move NON alphanumeric (A-Z) files")
            ;

    variables_map vm;
    store(parse_command_line(argc, argv, desc), vm);
    notify(vm);

    if (vm.count("help") || vm.size() == 0) {
        cout << desc << "\n";
        return 0;
    }

    if (vm.count("source")) {
        _srcPath = vm["source"].as<string > ();
        sorter.setSrcPath(_srcPath);
    }else {
        cout << "The source folder is required!" << endl;
        cout << desc << endl;
        return 0;
    }

    if (vm.count("destination")) {
        _dstPath = vm["destination"].as<string > ();
        sorter.setDstPath(_dstPath);
    }else if(!vm.count("destination") && vm.count("source")){
        _srcPath = vm["source"].as<string > ();
        sorter.setDstPath(_srcPath);
    }

    if (vm.count("interleave")) {
        _interleave = vm["interleave"].as<int > ();
        sorter.setTreeDepth(_interleave);
    }

    if (vm.count("no-rest")) {
        sorter.setRest(true);
    }

    sorter.createStructure(_dstPath, _interleave);
    sorter.sort();
    sorter.cleanStructure(_dstPath);


    return 0;
}