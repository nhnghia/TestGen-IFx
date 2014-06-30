/*
 * HitOrJump.h
 *
 *  Created on: 27 juin 2014
 *      Author: nhnghia
 */

#ifndef HITORJUMP_H_
#define HITORJUMP_H_
#include "Explorator.h"

namespace tsp {

class HitOrJump : public Explorator{
public:
	HitOrJump(const IfEngine* engine);
	virtual ~HitOrJump();
public:
	void explore(IfConfig* source, IfLabel* label, IfConfig* target);
	void visitAll(int depthlim);
};

} /* namespace tsp */

#endif /* HITORJUMP_H_ */
