/*
 * Statistics.h
 *
 *  Created on: 18-Feb-2014
 *      Author: cfilt
 */

#ifndef STATISTICS_H_
#define STATISTICS_H_

#include <string>
#include <map>
#include "../Lib/StringLib.h"
#include "boost/filesystem/operations.hpp"
#include "boost/algorithm/string/split.hpp"
#include "boost/algorithm/string/trim.hpp"
using namespace std;

class Statistics {
private:
	map<string,int> vocab_count;
public:
	Statistics(string dir);
	virtual ~Statistics();
};

#endif /* STATISTICS_H_ */
