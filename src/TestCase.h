/*
 * TestCase.h
 *
 *  Created on: 29 juin 2014
 *      Author: nhnghia
 */

#ifndef TESTCASE_H_
#define TESTCASE_H_

#include <vector>
#include <stdlib.h>
#include <iostream>
#include "Event.h"

namespace tsp {

class TestCase : public std::vector<Event*>{
public:
	TestCase();
	virtual ~TestCase();
	/**
	 * add all input/output/delay event in label to the test case
	 * @return : number of added events
	 */
	int add(IfLabel *label);
	void print(std::ostream&);
};

} /* namespace tsp */

#endif /* TESTCASE_H_ */

