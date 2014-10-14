/*
 * RandomExplorator.cpp
 *
 *  Created on: 2 juil. 2014
 *      Author: nhnghia
 */

#include "RandomExplorator.h"
#include <iostream>
namespace tsp {

RandomExplorator::RandomExplorator(IfEngine *engine) : Explorator(engine) {

}

RandomExplorator::~RandomExplorator() {
}

void RandomExplorator::visitAll(int depth) {
	Explorator::visitAll(depth);

	IfConfig *start = m_engine->start();

	//get all outgoing transitions from "start"
	transitions.clear();
	m_engine->run(start);

	for (currentDepth=0; currentDepth<maxDepth; currentDepth ++){
		//list the transitions
		int n = transitions.size();
		if (n == 0)
			break;

		/*
		cout <<endl <<"=============================" <<endl;

		cout <<"0. exit" <<endl;
		for (int i=0; i<n; i++){
			Transition t = transitions.at(i);
			cout << (i+1) <<". " <<t.label->string() <<endl;
		}

		//select one of transitions or exit
		int d = -1;
		//while (d < 0 || d > n){
			cout <<"Select (from 0 to " <<n <<"): ";
			std::cin >>d;
			cin.ignore();
			cin.get();
		}*/

		int d = int(rand() % n);	//random from 0 to n
		cout <<currentDepth <<". selected branch " <<d+1 <<"/" <<n <<endl;
		//get
		Transition t = transitions.at(d);
		//add t to testCase
		testCase.add(t.label);

		transitions.clear();
		m_engine->run(t.target);
	}
	Explorator::printTestCase();
}

void RandomExplorator::explore(IfConfig* source, IfLabel* label, IfConfig* target){
	if (source == NULL || label == NULL)
		return;

	Transition tran;
	tran.source = source;
	//I don't understand why need to copy while using pointer here
	//however if not, tran.label in transitions will lost
	tran.label = label->copy();
	tran.target = target;

	transitions.push_back(tran);
}

} /* namespace tsp */
