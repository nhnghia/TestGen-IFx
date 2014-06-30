/*
 * TestCase.cpp
 *
 *  Created on: 29 juin 2014
 *      Author: nhnghia
 */

#include "TestCase.h"

namespace tsp {
TestCase::TestCase(){
}
TestCase::~TestCase(){
}
void TestCase::print(std::ostream& os){
	int n = size();
	for (int i=0; i<n; i++)
		os << at(i)->toString() <<endl;
}
} /* namespace tsp */
