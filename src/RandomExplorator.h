/*
 * RandomExplorator.h
 *
 *  Created on: 2 juil. 2014
 *      Author: nhnghia
 */

#ifndef RANDOMEXPLORATOR_H_
#define RANDOMEXPLORATOR_H_
#include "Explorator.h"
#include <vector>
namespace tsp {

class RandomExplorator : public Explorator {
public:
	RandomExplorator(IfEngine *engine);
	virtual ~RandomExplorator();

	void visitAll(int depth);
	void explore(IfConfig* source, IfLabel* label, IfConfig* target);
private:
	struct Transition{
		IfConfig *source;
		IfLabel *label;
		IfConfig *target;
	};
	vector<Transition> transitions;
};

} /* namespace tsp */

#endif /* RANDOMEXPLORATOR_H_ */
