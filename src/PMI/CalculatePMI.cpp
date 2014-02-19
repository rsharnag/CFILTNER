/*
 * CalculatePMI.cpp
 *
 *  Created on: 19-Dec-2013
 *      Author: Rahul Sharnagat
 */

#include <cstdlib>
#include <string>
#include <math.h>
#include "CalculatePMI.h"

#define MAX_STRING 60
bool PMI::isSymbol(string a) {
	if (a.size() == 1)
		return std::find(syms.begin(), syms.end(), a[0]) != syms.end();
	return false;
}
void PMI::calculateVocabCount() {
	// Calculates bigram and unigram counts of words in the text
	string line;
	vector<string> words;
	inpfile.open(filename.c_str());
	if (!inpfile.is_open()) {
		cerr << "File could not be opened\n";
		exit(1);
	}
	while (!inpfile.eof()) {
		std::getline(inpfile, line);
		boost::trim(line);
		words.clear();
		boost::split(words, line, boost::is_any_of(" "),
				boost::token_compress_on);
		for (int i = 0; i < words.size(); i++) {
			vocab_count[words[i]] = vocab_count[words[i]] + 1;
			word_count++;
			if (word_count % 100000 == 0) {
				cout << "\rwords:" << word_count;
				fflush(stdout);
			}
		}

		string phrase = "";
		for (int i = 1; i < words.size() - 1; i++) {
			while (i < words.size() - 2 && isSymbol(words[i])) i++;
			if (i == words.size() - 1) break;
			int j = i + 1;
			phrase = words[i] + "_" + words[j];
			vocab_count[phrase] = vocab_count[phrase] + 1;
		}
	}
	cout << "\rTotal words:" << word_count << "\tUnique words:"
			<< vocab_count.size();
	fflush(stdout);
	for (map<string, int>::iterator iter = vocab_count.begin();
			iter != vocab_count.end();) {
		if (iter->second < min_count) {
			map<string, int>::iterator del = iter;
			iter++;
			vocab_count.erase(del);
		} else {
			iter++;
		}
	}
	cout << "\nUnique vocab:" << vocab_count.size();
	inpfile.close();
}
void PMI::calcPMI() {
	calculateVocabCount();
	inpfile.open(filename.c_str(),ios::in);
	string word, last_word, bigram_word;
	double score;
	int pa, pb;
	string line;
	while (!inpfile.eof()){
		std::getline(inpfile, line);
		boost::trim(line);
		vector<string> words;
		boost::split(words, line, boost::is_any_of(" "),
				boost::token_compress_on);
		last_word = "";
		pa = 0;
		pb = 0;
		for (int i = 0; i < words.size(); i++) {
			word = words[i];
			cout << words[i];
			if (vocab_count.find(word) != vocab_count.end())
				pb = vocab_count[word];
			bigram_word = last_word + "_" + word;
			if (vocab_count.find(bigram_word) != vocab_count.end()) {
				score = vocab_count[bigram_word] / (double) pa / (double) pb
						* word_count;
			} else
				score = 0;
			if (score > threshold) {
				outfile << "_" << word;
				cout << last_word << "_" << word << "\n";
				pb = 0;
			} else {
				outfile << " " << word;
			}
			pa = pb;
			last_word = word;
		}
		outfile << "\n";

	}
	inpfile.close();
}
PMI::PMI(string filepath) :
		threshold(100) {

	outfile.open("wiki_phrase.txt", std::ios::out);
	if (!outfile.is_open()) {
		cerr << "File could not be opened\n";
		exit(1);
	}
	min_count = 3;
	word_count = 0;
	char arr[] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_',
			'=', '+', '~', '`', '\'', '"', ',', '<', '>', '.', '/', '|', '+' };
	std::vector<char> temp(arr, arr + 25);
	syms = temp;
	filename=filepath;
}
