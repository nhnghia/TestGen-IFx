/* 
 Bfs.C : The search in break first search

 Last modification by Mounir LALLALI mlallali@gmail.com
 02/02/2009

 Main file: mainExplorator.C
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <execinfo.h>

#include "mainExplorator.h"
#include "state_queue.h"
#include "simulator.h"

/************* BFS *****************/

BfsExplorator::BfsExplorator(const IfEngine* engine, char* sc_file) :
		Explorator(engine, sc_file) {
	//readTestPurposes(sc_file);
	setTestPurposes();
	raiz = 0;
	hit_position = -1;
	label_id = 0;
	jump_counter = 0;
}
;

/********** BFS::VISIT_ALL *****************/
void BfsExplorator::visitAll(int depthlim) {
	StateNode jump_node;
	StateList StatePath;

	IfConfig* start = m_engine->start();
	m_queue.put(start, -1, -1);
	output_queue.put(start, -1, -1, -1);

	while (!m_queue.isEmpty()) {
		state_node = m_queue.get();
		//cout << "===>visit all===" <<state_node.depth;;
		if (state_node.state != NULL) {
			//state_node.state->printXML(cout);
			cout << "visitAll" <<endl;
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
				system(
						"$TestGenIF/lib/generate-path.sh ./output.suite ./output.label");
				output_queue.clear();
				m_queue.clear();
				state_node.state = jump_node.state;
				state_node.pos = jump_node.pos;
				state_node.depth = jump_node.depth;
				state_node.father = -1;
				raiz = jump_node.depth;
				jump_node.father = -1;
				jump_node.label_id = -1;
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

StateNode BfsExplorator::random_jump() {

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

void BfsExplorator::explore(IfConfig* source, IfLabel* label, IfConfig* target) {
	//cout << "===>explore\n";
	//fprintf( stderr,"Error(code:) at : %s (%s:%d)\n", __FUNCTION__, __FILE__, __LINE__);
	//CallTrace::print();
	//exit(0);
	long int depth;
	long int searched_depth = 0;
	bool exist = false;
	long int tmpDepth = -1;
	cout <<"   explorer" <<endl;

	if ((state_node.depth + 1) != hit_position) {
		if (output_queue.getPos(target) == -1) {
			m_queue.put(target, state_node.depth, state_node.pos);
			label_id++;
			print_label(label_id, label);
			output_queue.put(target, state_node.depth, state_node.pos,
					label_id);
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
			label_id++;
			print_label(label_id, label);
		}

		if (tmpDepth == -2) {
			StateNode source_node, target_node;
			output_queue.getNode(target, target_node);
			output_queue.getNode(source, source_node);
			output_queue.print_aldebaran_suite(source_node.pos, label_id,
					target_node.pos);
			output_queue.getPath(source_node);
			system(
					"$TestGenIF/lib/generate-path.sh ./output.suite ./output.label");
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
			output_queue.print_aldebaran_suite(source_node.pos, label_id,
					target_node.pos);
			output_queue.getPath(source_node);
			system(
					"$TestGenIF/lib/generate-path.sh ./output.suite ./output.label");
			m_queue.clear();
			output_queue.clear();
			target_state.state = target_node.state;
			target_state.pos = target_node.pos;
			target_state.depth = source_node.depth + 1;
			target_state.father = -1;
			m_queue.put(target_state);
			target_node.father = -1;
			target_node.label_id = -1;
			target_node.depth = source_node.depth + 1;
			output_queue.put(target_node);
		}
	}
}
