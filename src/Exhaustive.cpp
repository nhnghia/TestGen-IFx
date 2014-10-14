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
		Explorator(engine){
	this->isDfs = isDfs;
	numTestCases = 0;
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

		if (trans.size() == maxDepth){
			numTestCases ++;
			/*
			testCase.clear();
			int n = trans.size();
			for (int i=0; i<n; i++){
				Transition t = trans.at(i);
				testCase.add(t.label);
			}
			*/
			printTestCase();
		}else
			m_queue.push(trans);

		return;
	}
}



void Exhaustive::visitAll(int depth) {
	Explorator::visitAll(depth);

	//cout <<"visit all, depth: " << depth <<endl;

	//for (int i=0; i<3; i++)
	//	cout <<IfMessage::SIGNAME[i] <<endl;
	printf ("\nGenerating test cases: %10d ", 0);
	fflush(stdout);

	numTestCases = 0;

	currentQueue.clear();
	while (!m_queue.empty())
		m_queue.pop();

	IfConfig* start = m_engine->start();
	m_engine->run(start);

	printf (" - ");
		fflush(stdout);
	while(!m_queue.empty()){


		if (isDfs)
			currentQueue = m_queue.back();
		else
			currentQueue = m_queue.front();
		m_queue.pop();
		//get last element of currentQueue
		Transition t = currentQueue.back();

		if (t.target == NULL){
				numTestCases ++;
				/*
				testCase.clear();
				int n = currentQueue.size();
				for (int i=0; i<n; i++){
					Transition t = currentQueue.at(i);
					testCase.add(t.label);
				}
				*/
				printTestCase();
		}
		else
			m_engine->run(t.target);
	}

	 cout <<endl;
}


} /* namespace tsp */

