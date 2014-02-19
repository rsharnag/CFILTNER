#include<math.h>
#include "InfoIDF.h"
/*
 * InfoIDF.cpp
 *
 *  Created on: 14-Dec-2013
 *      Author: Rahul Sharnagat
 */
InfoIDF::InfoIDF(){
	df=0;
	cf=0;
	expectedIDF=0.0;
}
InfoIDF InfoIDF::incrDF() {
	InfoIDF* temp = this;
	temp->df++;
	return *temp;
}


InfoIDF InfoIDF::incrCF() {
	InfoIDF* temp = this;
	temp->cf++;
	return *temp;
}

void InfoIDF::calculateExpectedIDF(int totalDocs) {
	double mean = cf * 1.0 / totalDocs;
	double prob = -1.0 * log(1 - exp(-1.0 * mean)) / log(2); /// as per poisson distribution lambda^k e^(-lambda)/k! (mean)^0 = 1
	expectedIDF = prob;
}

