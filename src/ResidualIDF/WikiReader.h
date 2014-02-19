/*
 * WikiReader.h
 *
 *  Created on: 15-Dec-2013
 *      Author: cfilt
 */

#ifndef WIKIREADER_H_
#define WIKIREADER_H_
#include <vector>
#include <string>
#include <fstream>
#include "boost/filesystem/operations.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/trim.hpp"
#include "boost/algorithm/string/predicate.hpp"
#include "boost/algorithm/string/join.hpp"
using namespace std;

class Page{
private:
	vector<string> lines;
	string title;
public:
	Page();

	vector<string> getLines() const {
		return lines;
	}

	string getTitle() const {
		return title;
	}
	void appendLine(string line){
		lines.push_back(line);
	}
	string getRawText() const {
		return boost::join(lines,"\n");
	}
	void setLines(const vector<string>& lines) {
		this->lines = lines;
	}

	void setTitle(const string& title) {
		this->title = title;
	}

};


class WikiReader{
private:
	ifstream wikiFile;
	bool END;
public:
	WikiReader(const char*);
	Page getNextDoc();
	~WikiReader();
	bool isEOF();

};

#endif /* WIKIREADER_H_ */
