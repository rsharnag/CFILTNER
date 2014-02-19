/*
 * InfoIDF.h
 *
 *  Created on: 14-Dec-2013
 *      Author: cfilt
 */

#ifndef INFOIDF_H_
#define INFOIDF_H_

class InfoIDF {
private:
	int cf;
	int df; // no. of docs in which the term appears
	//whether they hold correct values
	double expectedIDF;
public:
	InfoIDF();

	/**
	 * Increments the document Frequency
	 * @return
	 */
	InfoIDF incrDF();

	/**
	 * Increments the Frequency of word
	 * @return
	 */
	InfoIDF incrCF();
	/**
	 * Directly calculates the expected IDF of each word
	 * @return
	 */
	void calculateExpectedIDF(int totalDocs);

	int getCf() const {
		return cf;
	}

	int getDf() const {
		return df;
	}

	double getExpectedIdf() const {
		return expectedIDF;
	}
};

#endif /* INFOIDF_H_ */
