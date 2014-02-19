/*
 * WikiReader.cpp
 *
 *  Created on: 15-Dec-2013
 *      Author: cfilt
 */
#include "WikiReader.h"
using namespace std;

WikiReader::WikiReader(const char* filePath){
	END=false;
	wikiFile.open(filePath);
	if(!wikiFile.is_open()) END=true;

}
WikiReader::~WikiReader(){
	wikiFile.close();

}
Page WikiReader::getNextDoc(){
	Page page;
	string line;
	bool pageEnd=false;
	while(!wikiFile.eof() && !pageEnd){
		std::getline(wikiFile,line);
		boost::trim(line);
		if(boost::starts_with(line,"<doc")){
			std::getline(wikiFile,line);
			boost::trim(line);
			page.setTitle(line);
			continue;
		}
		if(boost::starts_with(line,"</doc")){
			pageEnd=true;
			continue;
		}
		page.appendLine(line);
	}
	if(wikiFile.eof()) END=true;
	return page;
}
bool WikiReader::isEOF(){
	return END;
}
Page::Page(){

	title="";
}
