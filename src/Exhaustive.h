/*
 * Exhaustive.h
 *
 *  Created on: 27 juin 2014
 *      Author: nhnghia
 */

#ifndef BFS_H_
#define BFS_H_
#include <queue>
#include <stack>

#include "Explorator.h"

namespace tsp {

/**
 * A container that is either a Stack or a Queue depending on parameter of the constructor
 */
class Container{
public:
	/**
	 * Create a Stack if isStack==true, else a Queue
	 */
	Container(bool isStack);
	void push(IfConfig *s);
	IfConfig *pop();
	bool isEmpty();
private:
	bool isStack;
	queue<IfConfig *> queue;
	stack<IfConfig *> stack;
};

/**
 * Exhaustively visit based on DFS or BFS
 */
class Exhaustive: public Explorator {
public:
	Exhaustive(const IfEngine* engine, bool isDfs);
	virtual ~Exhaustive();

	void explore(IfConfig* source, IfLabel* label, IfConfig* target);
	void visitAll(int depthlim);
protected:
	Container *container;
private:
	int noVisitedBranches;
	TestCase testCase;
	void visit(IfConfig* source, IfLabel* label, IfConfig* target);
};

} /* namespace tsp */

#endif /* BFS_H_ */
