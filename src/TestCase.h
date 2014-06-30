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
	void print(std::ostream&);
};

} /* namespace tsp */

#endif /* TESTCASE_H_ */

