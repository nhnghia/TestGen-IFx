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

	raiz = 0;
	hit_position = -1;
	jump_counter = 0;
}
HitOrJump::~HitOrJump(){

}
void HitOrJump::visitAll(int depthlim) {
	Explorator::visitAll(depthlim);


	StateNode jump_node;
	StateList StatePath;

	IfConfig* start = m_engine->start();
	m_queue.put(start, -1, -1);
	output_queue.put(start, -1, -1);

	while (!m_queue.isEmpty()) {
		state_node = m_queue.get();
		if (state_node.state != NULL) {
			cout <<endl<< "visitAll" <<endl;
			if (state_node.depth > (depthlim - 1 + raiz)) {
				jump_counter++;
				printf(
						" >>>> a Jump from State at Depth %ld to State at Depth %ld - Depth Limit = %d  \n",
						raiz, state_node.depth, depthlim);
				printf(
						"_________________________________________________________________\n");

				m_queue.put(state_node);
				jump_node = random_jump();
				output_queue.getPath(jump_node);
				//system(
				//		"$TestGenIF/lib/generate-path.sh ./output.suite ./output.label");
				testCase.print(cout);
				testCase.clear();

				output_queue.clear();
				m_queue.clear();
				state_node.state = jump_node.state;
				state_node.pos = jump_node.pos;
				state_node.depth = jump_node.depth;
				state_node.father = -1;
				raiz = jump_node.depth;
				jump_node.father = -1;
				output_queue.put(jump_node);
			}
			m_engine->run(state_node.state);
		}
	}
	printf(" Fail! - All the Test Purposes are not satisfied.\n");
	printf(
			"_________________________________________________________________ \n");
	printf(" Number of Satisfied Test Purposes = %d/%d. \n",
			numFoundedTestPurposes, numTestPurposes);
	printf(" BFS - Number of executed JUMPS = %d. \n", jump_counter);
	printf(
			"_________________________________________________________________ \n\n");
	saveStat(0);
	saveTestPurposes();
	exit(1);
}

StateNode HitOrJump::random_jump() {

	srand(static_cast<unsigned>(time(NULL)));
	int pos;
	StateNode jump_node;
	stateQNode node;
	int size = m_queue.getSize();
	pos = int(rand() % (size)) + 1;
	node = m_queue.getNode(pos);
	output_queue.getNode(node.state, jump_node);
	return jump_node;
}

void HitOrJump::explore(IfConfig* source, IfLabel* label, IfConfig* target) {
	long int depth;
	long int searched_depth = 0;
	bool exist = false;
	long int tmpDepth = -1;
	cout <<".";

	if ((state_node.depth + 1) != hit_position) {
		if (output_queue.getPos(target) == -1) {
			m_queue.put(target, state_node.depth, state_node.pos);
			testCase.add(label);
			output_queue.put(target, state_node.depth, state_node.pos);
			depth = state_node.depth + 1;
		} else {
			exist = true;
			StateNode target_node;
			output_queue.getNode(target, target_node);
			depth = state_node.depth + 1;
		}

		if (numFoundedTestPurposes < numTestPurposes)
			tmpDepth = checkTestPurpose(source, label, target, depth);

		if (exist && (tmpDepth == -2 || tmpDepth >= 0)) {
			testCase.add(label);
		}

		if (tmpDepth == -2) {
			StateNode source_node, target_node;
			output_queue.getNode(target, target_node);
			output_queue.getNode(source, source_node);
			output_queue.getPath(source_node);
			//system(
			//		"$TestGenIF/lib/generate-path.sh ./output.suite ./output.label");
			testCase.print(cout);
			testCase.clear();

			saveStat(1);
			saveTestPurposes();
			exit(1);
		}

		if (tmpDepth >= 0) {
			raiz = tmpDepth;
			hit_position = tmpDepth;
			searched_depth = tmpDepth;
		}

		if (searched_depth > 0) {
			StateNode source_node, target_node;
			stateQNode target_state;
			output_queue.getNode(target, target_node);
			output_queue.getNode(source, source_node);
			output_queue.getPath(source_node);
			//system(
			//		"$TestGenIF/lib/generate-path.sh ./output.suite ./output.label");
			testCase.print(cout);
			testCase.clear();

			m_queue.clear();
			output_queue.clear();
			target_state.state = target_node.state;
			target_state.pos = target_node.pos;
			target_state.depth = source_node.depth + 1;
			target_state.father = -1;
			m_queue.put(target_state);
			target_node.father = -1;
			target_node.depth = source_node.depth + 1;
			output_queue.put(target_node);
		}
	}
}

} /* namespace tsp */
