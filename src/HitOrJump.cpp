/*
 * HitOrJump.cpp
 *
 *  Created on: 27 juin 2014
 *      Author: nhnghia
 */

#include "HitOrJump.h"

namespace tsp {

HitOrJump::HitOrJump(const IfEngine* engine) :
		Explorator(engine) {

}

HitOrJump::~HitOrJump() {
}

void HitOrJump::explore(IfConfig* source, IfLabel* label, IfConfig* target) {
}

void HitOrJump::visitAll(int depthlim) {
}

} /* namespace tsp */
