/*
 * stringLib.cpp
 *
 *  Created on: 18-Feb-2014
 *      Author: Rahul Sharnagat
 */
#include "StringLib.h"
#define DEBUG 2
namespace stringlib{
	char symarr[] = { '!', '@', '#', '$', '%', '^', '&', '*', '(', ')', '-', '_',
			'=', '+', '~', '`', '\'', '"', ',', '<', '>', '.', '/', '|', '+' };

}

using namespace std;
bool isSymbol(string a) {
	vector<char> syms(stringlib::symarr,stringlib::symarr+25);
	if (a.size() == 1)
		return std::find(syms.begin(), syms.end(), a[0]) != syms.end();
	return false;
}
bool isTag(string a){
	string tags[] ={} ;
	vector<string> t(tags,tags+5);
	return std::find(t.begin(), t.end(), a) != t.end();
}
vector<string> lineParser(string line){
	vector<string> words;
	vector<string> res;
	boost::trim(line);
	boost::split(words,line,boost::is_any_of(" "),boost::token_compress_on);
	for(int i=0;i<words.size();++i){
		vector<string> comp;
		boost::split(comp,words[i],boost::is_any_of("_"),boost::token_compress_on);
		if(comp.size()>1){
			string word;
			if(isTag(comp[comp.size()-1])){
				//recombine words
				for(int j=0;j<comp.size()-1;++j){
					word+=(comp[i]+"_");
				}
				word = word.substr(0,word.length()-1);
				res.push_back(word);
			}
		}
		else{
			res.push_back(words[i]);
		}
	}
	return res;
}


/**
 * Calculates Unigram and bigram counts of phrases
 *
 */

void calculateVocabCount(ifstream& inpfile,map<string,int>& vocab_count,int min_count){
		string line;
		vector<string> words;
		int word_count=0;
		while (!inpfile.eof()) {
			std::getline(inpfile, line);

			words= lineParser(line);
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
		if(DEBUG>1)
			cout << "\rTotal words:" << word_count << "\tUnique words:"
				<< vocab_count.size();
		fflush(stdout);
		if(min_count>0){
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
		}
		if(DEBUG>1)
			cout << "\nUnique vocab after min filter:" << vocab_count.size();
		inpfile.close();
}

/**
 * parser underscore parsed line
 */

