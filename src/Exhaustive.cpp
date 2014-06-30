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
		Explorator(engine) {
	container = new Container(isDfs);
	noVisitedBranches = 0;
}

Exhaustive::~Exhaustive() {
}

/**
 * visit a transition
 * this method is called automatically by engine
 */
void Exhaustive::explore(IfConfig* source, IfLabel* label, IfConfig* target) {
	//at each state, visit only one branch
	if (noVisitedBranches == 1)
		return;
	noVisitedBranches ++;

	visit(source, label, target);

	if (currentDepth < maxDepth && target != NULL){
		container->push(target);
	}
}

void Exhaustive::visit(IfConfig* source, IfLabel* label, IfConfig* target) {
	int n = label->getLength();
	for (int i=0; i<n; i++){
		Event *ev = Event::parser(label->getAt(i));
		if (ev != NULL){
			testCase.push_back(ev);
		}
	}
	if (testCase.size() == maxDepth || target == NULL)
		testCase.print(std::cout);
}


void Exhaustive::visitAll(int depth) {
	Explorator::visitAll(depth);

	IfConfig* start = m_engine->start();
	container->push(start);

	while (!container->isEmpty() && currentDepth < depth){
		std::cout <<"visitAll==="<<endl;
		currentDepth ++;

		IfConfig *node = container->pop();

		noVisitedBranches = 0;

		//visit all outgoing transitions from the state "node"
		m_engine->run(node);
	}
}





//Container
Container::Container(bool isStack) {
	this->isStack = isStack;
}

void Container::push(IfConfig* s) {
	if (isStack){
		stack.push(s);
	}else
		queue.push(s);
}

IfConfig* Container::pop() {
	IfConfig *s;
	if (isStack){
		 s = stack.top();
		 stack.pop();
	}else{
		s = queue.front();
		queue.pop();
	}
	return s;
}

bool Container::isEmpty(){
	if (isStack)
		return stack.empty();
	else
		return queue.empty();
}
} /* namespace tsp */

