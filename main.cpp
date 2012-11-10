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
namespace po = boost::program_options;

po::options_description initOptions() {
    po::options_description desc("Option List");

    desc.add_options()
            ("help", "Print this page")
            ("source", po::value<string > (), "Source Folder(s) where to look for the media data")
            ("destination", po::value<string > (), "Destination Folder where to reallocate the files")
            ("interleave", po::value<int>(), "the amount of sub-folder to create within the sorted folder. Example --interleave=1 would generate a structure like $DEST_FOLDER/A/AA")
            ;


}

/*
 * Main function for sortit 
 */
int main(int argc, char** argv) {
    SortIt sorter;
    IOSorter iosorter;
    string _dstPath;
    string _srcPath;


    po::options_description desc("Option List");

    desc.add_options()
            ("help", "Print this page")
            ("source", po::value<string > (), "Source Folder(s) where to look for the media data")
            ("destination", po::value<string > (), "Destination Folder where to reallocate the files")
            ("interleave", po::value<int>(), "the amount of sub-folder to create within the sorted folder. Example --interleave=1 would generate a structure like $DEST_FOLDER/A/AA")
            ;

    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, desc), vm);
    po::notify(vm);

    if (vm.count("help")) {
        cout << desc << "\n";
    }

    if (vm.count("source")) {
        _srcPath = vm["source"].as<string > ();
        sorter.setSrcPath(_srcPath);
    }

    if (vm.count("destination")) {
        _dstPath = vm["destination"].as<string > ();
        sorter.setDstPath(_dstPath);
    }

    sorter.createStructure(_dstPath, 2);
    sorter.sort();
    
    
    return 0;
}



//    else {
//        _srcPath = iosorter.getPath("Source Path");
//    }
//    else {
//        _dstPath = iosorter.getPath("Destination Path");
//    }