/*
 * HitOrJump.h
 *
 *  Created on: 27 juin 2014
 *      Author: nhnghia
 */

#ifndef HITORJUMP_H_
#define HITORJUMP_H_
#include "Explorator.h"
#include <vector>

namespace tsp {

class HitOrJump: public Explorator {
public:
	HitOrJump(const IfEngine* engine);
	virtual ~HitOrJump();
	void explore(IfConfig* source, IfLabel* label, IfConfig* target);
	void visitAll(int depthlim);

protected:
	long int visit(const IfConfig* state, long int depth);

	StateNode random_jump();
private:

	StateQueue m_queue;
	stateQNode state_node;
	StateList seq;
	long int raiz;
	long int hit_position;
	int jump_counter;

	void addLabelsToTestCase(vector<IfLabel *> lst);
};

} /* namespace tsp */

#endif /* HITORJUMP_H_ */
