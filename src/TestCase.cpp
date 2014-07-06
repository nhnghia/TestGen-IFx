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
	//no need delays at the end of test case
	//remove the last delays
	int i=n-1;
	for (i=n-1; i>=0; i--){
		Event *ev = at(i);
		//ev is not Delay
		if (dynamic_cast<Delay*>(ev) == NULL){
			break;
		}
	}
	//cut the delays at the end of test case
	if (i < n-1){
		erase(begin()+i+1, end());
	}
	n = i+1;
	for (int i=0; i<n; i++)
		os << at(i)->toString() <<endl;
}

int TestCase::add(IfLabel *label){

	int n=label->getLength();
	int d=0;
	for (int i=0; i<n; i++){
		Event *ev = Event::parser(label->getAt(i));
		if (ev != NULL){
			d++;
			TestCase::push_back(ev);
		}
	}
	return d;
}
map<string,TestCase> TestCase::project() {
	map<string,TestCase> localTestCase;

	return localTestCase;
}

} /* namespace tsp */

