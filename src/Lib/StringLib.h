/*
 * StringLib.h
 *
 *  Created on: 18-Feb-2014
 *      Author: cfilt
 */

#ifndef STRINGLIB_H_
#define STRINGLIB_H_
#include <map>
#include <fstream>
#include <vector>
#include <string>
#include <locale>
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/trim.hpp"
using namespace std;

extern bool isSymbol(string a);
extern void calculateVocabCount(ifstream& inpfile,map<string,int>& vocab_count,int min_count=0);
extern vector<string> lineParser(string line);
#endif /* STRINGLIB_H_ */
