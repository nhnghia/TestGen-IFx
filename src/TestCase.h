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
#include <map>
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
	/**
	 * get a set of local test cases
	 * @return a multimap, each element is <name,testCase> where "name" is name of component to test,
	 * "testcase" is local test case of this tester
	 * note: the local test case is "inverse" of local trace.
	 */
	map<string,TestCase> project();
};

} /* namespace tsp */

#endif /* TESTCASE_H_ */

