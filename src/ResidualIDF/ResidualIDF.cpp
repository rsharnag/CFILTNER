/*
 * ResidualIDF.cpp
 *
 *  Created on: 14-Dec-2013
 *      Author: Rahul Sharnagat
 */

#include "ResidualIDF.h"
namespace fs = boost::filesystem;
using namespace std;
void ResidualIDF::calculateInfoWiki(const char* wikiPath) {
	WikiReader wikiReader(wikiPath);
	while (!wikiReader.isEOF()) {
		Page page = wikiReader.getNextDoc();
		totalDocs++;
		map<string, int> curDoc;
		vector<string> lines = page.getLines();
		for (vector<string>::iterator iter = lines.begin(); iter != lines.end();
				++iter) {
			string line = *iter;
			vector<string> words;
			boost::split(words, line, boost::is_any_of(" "),
					boost::token_compress_on);
			for (int i = 0; i < words.size(); i++) {
				map<string, InfoIDF>::iterator it;
				if ((it = wordVals.find(words[i])) != wordVals.end()) {
					it->second.incrCF();
				} else {
					InfoIDF temp;
					temp.incrCF();
					wordVals[words[i]] = temp;
				}
				curDoc[words[i]] = 1;
			}
		}

		for (map<string, int>::iterator iter = curDoc.begin();
				iter != curDoc.end(); ++iter) {
			wordVals[iter->first].incrDF();
		}

	}
}
void ResidualIDF::calculateInfoFile(string file) {
	ifstream inp_file;
	inp_file.open(file.c_str());
	cout << "Processing:" << file << "\n";
	string line; // considered as document
	map<string, int> curDoc;
	while (!inp_file.eof()) {
		getline(inp_file, line);
		map<string, int> curDoc;
		boost::trim(line);
		totalDocs += 1;
		vector<string> words;
		boost::split(words, line, boost::is_any_of("/ "),
				boost::token_compress_on);
		for (int i = 0; i < words.size(); i++) {
			map<string, InfoIDF>::iterator it;
			if ((it = wordVals.find(words[i])) != wordVals.end()) {
				it->second.incrCF();
			} else {
				InfoIDF temp;
				temp.incrCF();
				wordVals[words[i]] = temp;
			}
			curDoc[words[i]] = 1;
		}
		for (map<string, int>::iterator iter = curDoc.begin();
				iter != curDoc.end(); ++iter) {
			wordVals[iter->first].incrDF();
		}
	}

}
void ResidualIDF::calculateInfo(string dir) {
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
					//Do processing on file
					ifstream inp_file;
					inp_file.open(dir_itr->path().string().c_str());
					cout << "Processing:" << dir_itr->path().string() << "\n";
					string line;
					totalDocs++;
					map<string, int> curDoc;
					while (!inp_file.eof()) {
						std::getline(inp_file, line);
						boost::trim(line);
						vector<string> words;
						boost::split(words, line, boost::is_any_of("/ "),
								boost::token_compress_on);
						for (int i = 0; i < words.size(); i++) {
							map<string, InfoIDF>::iterator it;
							if ((it = wordVals.find(words[i]))
									!= wordVals.end()) {
								wordVals[words[i]] =
										wordVals[words[i]].incrCF();
							} else {
								InfoIDF temp;
								temp.incrCF();
								wordVals[words[i]] = temp;
							}
							curDoc[words[i]] = 1;
						}
					}

					for (map<string, int>::iterator iter = curDoc.begin();
							iter != curDoc.end(); ++iter) {
						wordVals[iter->first].incrDF();
					}

				} else {
					//Weird file
					cerr << "Weird File:" << dir_itr->path().string() << "\n";
				}
			} catch (exception & ex) {
				cerr << "Exception caught";
			}

		}
	}
}
bool mapComp(pair<string, double> a, pair<string, double> b) {
	return a.second > b.second;
}
void ResidualIDF::printSortedIDFs(ofstream& out) {
	for (map<string, InfoIDF>::iterator iter = wordVals.begin();
			iter != wordVals.end(); ++iter) {
		InfoIDF* idf = &(iter->second);
		if (idf->getCf() > 10) {
			idf->calculateExpectedIDF(totalDocs);
			//wordMap[iter->first] = (-1.0 * log(idf->getDf() * (1.0 / totalDocs)+idf->getCf()*(1.0/idf->getDf()))
//				/ log(2.0) );//- idf->getExpectedIdf());
			wordMap[iter->first] = (-1.0 * log(idf->getDf() * (1.0 / totalDocs))
					/ log(2.0) - idf->getExpectedIdf());
			//wordMap[iter->first] *= (1.0 * idf->getCf()) / idf->getDf();
		}
	}
	vector<pair<string, double> > mapVec(wordMap.begin(), wordMap.end());
	sort(mapVec.begin(), mapVec.end(), mapComp);
	out
			<< "word\tResidual IDF\tfrequency\tdocument Frequecy\tExpected IDF\tIDF\n";
	for (vector<pair<string, double> >::iterator iter = mapVec.begin();
			iter != mapVec.end(); ++iter) {
		double temp = (-1.0
				* log(wordVals[iter->first].getDf() * 1.0 / totalDocs))
				/ log(2.0);
		cout << iter->first << "\t" << iter->second << "\t"
				<< wordVals[iter->first].getCf() << "\t"
				<< wordVals[iter->first].getDf() << "\n";
		out << iter->first << "\t" << iter->second << "\t"
				<< wordVals[iter->first].getCf() << "\t"
				<< wordVals[iter->first].getDf() << "\t"
				<< wordVals[iter->first].getExpectedIdf() << "\t" << temp
				<< "\n";
	}
}

