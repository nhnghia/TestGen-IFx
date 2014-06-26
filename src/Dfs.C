/* 

 Dfs.C : The search in depth first search

 Last modification by Mounir LALLALI mlallali@gmail.com
 03/04/2008

 Main file: mainExplorator.C
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include "mainExplorator.h"
#include "state_stack.h"
#include "simulator.h"

/************* DFS ****************/

DfsExplorator::DfsExplorator(const IfEngine* engine, char* sc_file) :
		Explorator(engine, sc_file) {
	readTestPurposes(sc_file);
	cout << "Init\n";
	raiz = 0; //"raiz" is the root node.The first one to be searched (Recommended: "raiz =0").
}
;

/********** DFS::VISIT_ALL *****************/
void DfsExplorator::visitAll(int depthlim) {

	int jump_counter = 0; /* it counts the number of total jumps done during the exploration */
	StateNode jump_node;

	IfConfig* start = m_engine->start();
	start->setMark(REACHED);
	m_stack.put(start, -1, -1);
	output_queue.put(start, -1, -1, NULL);

	while (!m_stack.isEmpty()) {
		state_node = m_stack.get();
		cout << "visitAll" <<endl;
		if (state_node.state != 0) {
			m_engine->run(state_node.state);
		}
	}

	printf(" Fail! - All the Stop Conditions are not Founded. \n");
	printf(
			"_________________________________________________________________ \n");
	//printf(" Number of Satisfied Conditions = %d/%d. \n", NFoundSC,NStopConditions);
	printf(" DFS - Number of executed JUMPS = %d. \n", jump_counter);
	printf(
			"_________________________________________________________________ \n\n");

}

long int DfsExplorator::visit(const IfConfig* state, long int depth,
		long int positionState) {
	FILE *f;

	if ((f = fopen("output.sta", "a")) != NULL) {
		state->print(f);
	}

	int hitDepth = 1;	//checkStateSC(state,depth,positionState);
	cout << "Visit" << endl;
	CallTrace::print();
	return hitDepth;
}

void DfsExplorator::explore(IfConfig* source, IfLabel* label,
		IfConfig* target) {
	source->setMark(REACHED);
	cout << "   Explore" << endl;
	cout << "       " << label->string() <<endl;
	if (target->getMark() != REACHED)
		m_stack.put(target, state_node.depth, state_node.pos);
}
