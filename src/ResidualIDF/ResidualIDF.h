/*
 * ResidualIDF.h
 *
 *  Created on: 14-Dec-2013
 *      Author: cfilt
 */

#ifndef RESIDUALIDF_H_
#define RESIDUALIDF_H_
#include <map>
#include <string>
#include <fstream>
#include <math.h>
#include "WikiReader.h"
#include "boost/filesystem/operations.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/trim.hpp"
#include"InfoIDF.h"
using namespace std;
class ResidualIDF{
private:
	map<string,double> wordMap;
	map<string,InfoIDF> wordVals;
	int totalDocs;
public:
	/**
	 * Constructor for Residual IDF class
	 */
	ResidualIDF(){
		totalDocs=0;
	}
	/**
	 * Calculates IDF info for the documents in the specified directory
	 * @param[in] dir  directory path to docs
	 * @return
	 */
	void calculateInfo(string dir);
	/**
	 * Calculates IDF info for the wiki text
	 * @param[in] dir  Path to wiki text
	 * @return
	 */
	void calculateInfoWiki(const char* wikiPath);
	void calculateInfoFile(string wikiPath);
	void printSortedIDFs(ofstream& out);
};
#endif /* RESIDUALIDF_H_ */
