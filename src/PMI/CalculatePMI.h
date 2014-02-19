/*
 * CalculatePMI.h
 *
 *  Created on: 19-Dec-2013
 *      Author: cfilt
 */

#ifndef CALCULATEPMI_H_
#define CALCULATEPMI_H_
#include <string>
#include <map>
#include <fstream>
#include <vector>
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/trim.hpp"
using namespace std;
class PMI{
private:
	ifstream inpfile;
	ofstream outfile;
	int min_count,word_count;
	const int threshold;
	string filename;
	map<string,int> vocab_count;
	vector<char> syms;
	/**
	 * Calculate Unigram and bigram counts
	 */
	void calculateVocabCount();
	/**
	 * Calculate PMI of words
	 */
	void trainPMI();
	bool isSymbol(string s);
public:
	PMI(string filepath);
	void calcPMI();

};


#endif /* CALCULATEPMI_H_ */
