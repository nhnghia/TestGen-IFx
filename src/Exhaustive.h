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
#include <vector>

#include "Explorator.h"
#include "simulator.h"
#include "explorator.h"
namespace tsp {


/**
 * Exhaustively visit based on DFS or BFS
 */
class Exhaustive: public Explorator {
public:
	Exhaustive(const IfEngine* engine, bool isDfs);
	virtual ~Exhaustive();

	void explore(IfConfig* source, IfLabel* label, IfConfig* target);
	void visitAll(int depthlim);
private:
	void visit(IfConfig* source, IfLabel* label, IfConfig* target);
	bool isDfs;

struct Transition{
		IfConfig *source;
		IfConfig *target;
		IfLabel  *label;
	};
	queue<vector<Transition> > m_queue;
	vector<Transition> currentQueue;
};

} /* namespace tsp */

#endif /* BFS_H_ */
