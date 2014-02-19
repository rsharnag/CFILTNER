/*
 * Statistics.cpp
 *
 *  Created on: 18-Feb-2014
 *      Author: cfilt
 */

#include "Statistics.h"

using namespace std;
namespace fs = boost::filesystem;
/**
 * Constructor for unsupervised statistics generator
 */

Statistics::Statistics(string dir) {
	// TODO Auto-generated constructor stub
	fs::path full_path(fs::initial_path<fs::path>());
	full_path = fs::system_complete(fs::path(dir));
	if (!fs::exists(full_path)) {
		cerr << "\nPath not found: " << full_path.string();
		return;
	}
	if (fs::is_directory(full_path)) {
		cout << "Processing directory:" << full_path.string() << "\n";
		fs::directory_iterator dir_end;
		for (fs::directory_iterator dir_itr(full_path); dir_itr != dir_end;
				++dir_itr) {
			try {
				if (fs::is_directory(dir_itr->status())) {
					//cout<<"Dir:"<<dir_itr->path().string()<<"\n";
					//For future how to recurse in directory structure
				} else if (fs::is_regular_file(dir_itr->status())) {
					ifstream inp_file;
					inp_file.open(dir_itr->path().string().c_str());
					if(inp_file.is_open()){
						cout << "Processing:" << dir_itr->path().string() << "\n";
						calculateVocabCount(inp_file,vocab_count);
					}
				}
			}
			catch(exception& ex){
				cerr<<"Exception caught:"<<ex.what();
			}
		}
	}
}

Statistics::~Statistics()
{
// TODO Auto-generated destructor stub
}

