/*
 * NER.cpp
 *
 *  Created on: 15-Dec-2013
 *  Author: Rahul Sharnagat
 *
 */

#include "ResidualIDF/ResidualIDF.h"
#include "PMI/CalculatePMI.h"
#include "Statistics/Statistics.h"
/*
 * Main method for Running NER system
 */
int main() {

	ResidualIDF s;
	ofstream out;
//	out.open("sortedOuputWiki.txt", ios::out);
//	s.calculateInfoFile("/home/cfilt/corpus/ilci_parallel/tourism/en.txt");

	s.printSortedIDFs(out);
	out.close();
//	PMI p("/home/cfilt/wikiDump/hindi/hindi_text.txt");
//	p.calcPMI();
	//Statistics code
	Statistics stat("/home/cfilt/Dropbox/MTP/corpus/NE-tagged Corpora/HindiCorpus");

	return 0;

}

