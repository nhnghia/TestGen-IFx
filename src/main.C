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
#include <sys/time.h>

#include "state_queue.h"
#include "state_stack.h"

#include "Exhaustive.h"
#include "CallTrace.h"
#include "HitOrJump.h"
#include "Explorator.h"
#include "RandomExplorator.h"

void handler(int sig) {
	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	tsp::CallTrace::print();
}


/* ===== MAIN ===== */
int main(int argc, char * argv[]) {
	struct timeval tp;
	gettimeofday(&tp, NULL);
	long int ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;

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
			else if (!strcmp(argv[i], "-hoj"))
				traversal = HIT_OR_JUMP;
			else if (!strcmp(argv[i], "-ran"))
				traversal = RANDOM;
			else if (!strcmp(argv[i], "-p"))
				sc_file = (i == argc - 1) ? NULL : argv[i + 1];
			else if (!strcmp(argv[i], "-d")) {
				if (i < argc) {
					depthlim = atoi(argv[i + 1]);
				}
			}
		}
	}

	IfEngine* engine = new IfIterator();
	tsp::Explorator *expl = NULL;
	if (traversal == BFS || traversal == DFS) {
		tsp::Exhaustive *expl = new tsp::Exhaustive(engine, traversal == BFS);
		expl->visitAll(depthlim);
	}
	else if (traversal == HIT_OR_JUMP) {
		expl = new tsp::HitOrJump(engine);
	}
	else if (traversal == RANDOM){
		expl = new tsp::RandomExplorator(engine);
	}
	if (expl)
		expl->visitAll(depthlim);

	gettimeofday(&tp, NULL);
	long int ms2 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

	cout <<endl <<"Elapsed time: " <<(ms2 - ms)/100.0 <<" seconds" <<endl;
	return 0;
}
