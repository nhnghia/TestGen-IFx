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
#include <set>

namespace tsp {

/**
 * Test Case is a sequence of @link Event
 */
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
	 * concat two Test cases
	 * @param t
	 * @return
	 */
	TestCase concat(TestCase t);

	/**
	 * get a local test case of a partner
	 * @param partner name of the partner
	 * @return a local test case of tester to test this partner
	 * note: the local test case is an "inverse" of local trace.
	 */
	TestCase project(string partner);

	/**
	 * print in MSC text http://www.mcternan.me.uk/mscgen/
	 * @param
	 */
	void printMsc(ostream &);

	/**
	 * Sum up a sequence of consecutive delays to unique one
	 * and remove the last event if it is a delay
	 */
	TestCase optimize();


	/**
	 * @return set of partners involved in this test case
	 */
	set<string> getPartners();
};

} /* namespace tsp */

#endif /* TESTCASE_H_ */

