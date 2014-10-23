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
#include <cstdlib>

/**
 * hander error, exception happened in the program
 * @param sig
 */
void handler(int sig) {
	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	tsp::CallTrace::print();
}


class Stat{
	long int ms;
public:
	tsp::Explorator *expl;
	void begin(){
		struct timeval tp;
		gettimeofday(&tp, NULL);
		ms = tp.tv_sec * 1000 + tp.tv_usec / 1000;
		expl = NULL;
	}
	void end(){
		struct timeval tp;
		gettimeofday(&tp, NULL);
		long int ms2 = tp.tv_sec * 1000 + tp.tv_usec / 1000;

		//Statistic
		printf("_________________________________________________________________\n");
		printf("STATISTIC:\n");
		cout <<"  - Number of test cases generated: " << expl->numberOfTestCasesGenerated <<endl ;
		cout <<"  - Elapsed time                  : " <<(ms2 - ms)/100.0 <<" seconds" <<endl <<endl ;
		//printf("_________________________________________________________________\n");
	}
};

Stat stat;
void exiting(){
	stat.end();
}

/* ===== MAIN ===== */
int main(int argc, char * argv[]) {
	stat.begin();
	std::atexit(exiting);
	signal(SIGSEGV, handler);   // install our handler of errors

	static const unsigned DEFAULTDEPTH = 10;
	int depthlim = DEFAULTDEPTH;     // maxdepth
	char* tc_folder = NULL;  		 // folder containing test cases
	bool isProject = false;			 // project test cases into local ones or not


	enum {
		BFS, DFS, RANDOM, HIT_OR_JUMP, INTERACTIVE
	} traversal = BFS;

	if (argc < 3) {
		fprintf(stderr,
				"\n Usage: %s [options]\n",
				argv[0]);
		fprintf(stderr, " where [options] may be\n");
		fprintf(stderr, "   . exploration options [-bfs|-dfs|-ran|-hoj|-ite] : exploration policy:\n");
		fprintf(stderr, "             -bfs : breadth first\n");
		fprintf(stderr, "             -dfs : depth first\n");
		fprintf(stderr, "             -ran : random\n");
		fprintf(stderr, "             -hoj : hit-or-jump\n");
		fprintf(stderr, "             -ite : interactive in command line\n");
		fprintf(stderr, "     [-d integer] : maximal exploration depth\n");
		fprintf(stderr, "   . test case options\n");
		fprintf(stderr, "     [-o filename]: path to a folder using to contain test cases generated (default is the current folder)\n");
		fprintf(stderr, "     [-sp]        : split test cases to local ones\n");
		fprintf(stderr, "\n");
		return 1;
	}
	printf("_________________________________________________________________\n");
	printf("INPUT:\n");

	for (int i = 1; i < argc; i++) {
		if (argv[i][0] == '-') {
			if (!strcmp(argv[i], "-bfs")){
				traversal = BFS;
				printf("  - Exploration policy: BFS\n");
			}else if (!strcmp(argv[i], "-dfs")){
				traversal = DFS;
				printf("  - Exploration policy: BFS\n");
			}else if (!strcmp(argv[i], "-hoj")){
				traversal = HIT_OR_JUMP;
				printf("  - Exploration policy: Hit-or-Jump\n");
			}else if (!strcmp(argv[i], "-ran")){
				traversal = RANDOM;
				printf("  - Exploration policy: Random\n");
			}else if (!strcmp(argv[i], "-o")){
				tc_folder = (i == argc - 1) ? NULL : argv[i + 1];
				printf("  - Test cases output folder: %s\n", tc_folder);
			}else if (!strcmp(argv[i], "-d")) {
				if (i < argc) {
					depthlim = atoi(argv[i + 1]);
					printf("  - Maximal exploration depth: %d\n", depthlim);
				}
			}
			else if (!strcmp(argv[i], "-sp")){
				isProject = true;
				printf("  - Project global test cases on local ones\n");
			}
		}
	}

	printf("_________________________________________________________________\n");
	printf("PROCESSING ... \n");
	IfEngine* engine = new IfIterator();
	tsp::Explorator *expl = NULL;

	if (traversal == BFS || traversal == DFS) {
		expl = new tsp::Exhaustive(engine, traversal == BFS);
	}
	else if (traversal == HIT_OR_JUMP) {
		expl = new tsp::HitOrJump(engine);
	}
	else if (traversal == RANDOM){
		expl = new tsp::RandomExplorator(engine);
	}

	if (expl){
		stat.expl = expl;

		expl->isProjectTestCases = isProject;
		if (tc_folder)
			expl->testCasesFolder = string(tc_folder);
		expl->numberOfTestCasesGenerated = 0;

		expl->visitAll(depthlim);
	}

	//processing time

	return 0;
}
