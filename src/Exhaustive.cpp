/*
 * Exhaustive.cpp
 *
 *  Created on: 27 juin 2014
 *      Author: nhnghia
 */

#include "Exhaustive.h"

namespace tsp {
enum{
	VISITED, UNVISITED
};

Exhaustive::Exhaustive(const IfEngine* engine, bool isDfs) :
		Explorator(engine)
{

}

Exhaustive::~Exhaustive() {
}

/**
 * visit a transition
 * this method is called automatically by engine
 */
void Exhaustive::explore(IfConfig* source, IfLabel* label, IfConfig* target) {
	//at each state, visit only one branch
	//cout <<currentQueue.size() <<"/" <<maxDepth <<"- visite : " << label->string() <<endl;
	if (target != NULL && currentQueue.size() < maxDepth){
		vector<Transition> trans (currentQueue);
		Transition t;
		t.source = source->copy();
		t.target = target->copy();
		t.label  = label->copy();
		trans.push_back(t);
		m_queue.push(trans);
	}
	else{
		printTestCase();
	}

}

void Exhaustive::printTestCase(){
	numTestCases ++;
	TestCase testCase;
	int n = currentQueue.size();
	for (int i=0; i<n; i++){
		Transition t = currentQueue.at(i);
		testCase.add(t.label);
	}
	cout <<"--------------" <<endl;
		cout <<"Test case:" <<numTestCases <<endl;
		testCase.print(cout);
		cout <<"--------------" <<endl;
}


void Exhaustive::visitAll(int depth) {
	Explorator::visitAll(depth);

	cout <<"visit all, depth: " << depth <<endl;
	numTestCases = 0;
	currentQueue.clear();
	while (!m_queue.empty())
		m_queue.pop();

	IfConfig* start = m_engine->start();
	m_engine->run(start);

	while(!m_queue.empty()){
		currentQueue = m_queue.front();
		m_queue.pop();
		//get last element of currentQueue
		Transition t = currentQueue.back();

		m_engine->run(t.target);
	}

	cout <<endl <<"Number of test cases: " <<numTestCases<<endl;
}



} /* namespace tsp */

