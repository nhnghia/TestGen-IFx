/*
 Last modification by Huu-Nghia NGUYEN <nhnghia@me.com>
 27/06/2014
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <signal.h>
#include <execinfo.h>

#include "state_queue.h"
#include "state_stack.h"

#include "Exhaustive.h"
#include "CallTrace.h"

void handler(int sig) {
	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	tsp::CallTrace::print();
}


/* ===== MAIN ===== */
int main(int argc, char * argv[]) {
	signal(SIGSEGV, handler);   // install our handler

	static const unsigned DEFAULTDEPTH = 20;
	int depthlim = DEFAULTDEPTH;     // maxdepth
	char* sc_file = NULL;  // Stop Conditions File

	enum {
		BFS, DFS, RANDOM, HIT_OR_JUMP, INTERACTIVE
	} traversal = BFS;

	if (argc < 3) {
		fprintf(stderr,
				"\n Usage: %s [-traversal(bfs|dfs|ran|hoj|ite) -maxdepth(integer)? -p(test_purposes_file)?]\n\n",
				argv[0]);
		return 1;
	}


	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (!strcmp(argv[i], "-bfs"))
				traversal = BFS;
			else if (!strcmp(argv[i], "-dfs"))
				traversal = DFS;
			else if (!strcmp(argv[i], "-p"))
				sc_file = (i == argc - 1) ? NULL : argv[i + 1];
			else if (!strcmp(argv[i], "-d")) {
				if (i != argc - 1) {
					char *p_conv;
					int number = (int) strtol(argv[i + 1], &p_conv, 10);
					if (*p_conv == 0)
						depthlim = number;
				}
			}
		}
	}

	IfEngine* engine = new IfIterator();
	if (traversal == BFS || traversal == DFS) {
		tsp::Exhaustive* bfs = new tsp::Exhaustive(engine, traversal == BFS);
		bfs->visitAll(depthlim);
	}
	if (traversal == DFS) {
		//DfsExplorator* dfs = new DfsExplorator(engine, sc_file);
		//dfs->visitAll(depthlim);
	}
	return 0;
}
