/*
 Last modification by Mounir LALLALI mlallali@gmail.com
 02/02/2009
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <signal.h>
#include <execinfo.h>

#include "mainExplorator.h"
#include "state_queue.h"
#include "state_stack.h"
#include "simulator.h"

void CallTrace::print() {
	int j, nptrs;
#define SIZE 100
	void *buffer[100];
	char **strings;

	nptrs = backtrace(buffer, SIZE);
	printf("backtrace() returned %d addresses\n", nptrs);

	/* The call backtrace_symbols_fd(buffer, nptrs, STDOUT_FILENO)
	 would produce similar output to the following: */

	strings = backtrace_symbols(buffer, nptrs);
	if (strings == NULL) {
		perror("backtrace_symbols");
		exit(EXIT_FAILURE);
	}

	for (j = 0; j < nptrs; j++)
		printf("%s\n", strings[j]);

	free(strings);
}

Explorator::Explorator(const IfEngine* engine, char* sc_file) :
		IfDriver(engine) {
	stateNumber = 0;

	srand(static_cast<unsigned>(time(NULL)));
	srand((unsigned) time(0));

	output_label.open("output.label", ios_base::app);
	output_stat.open("output.stat", ios_base::app);

	if (!output_label)
		printf("\n >>> File 'output.label' not open ! \n");
	if (!output_stat)
		printf("\n >>> File 'output.stat' not open ! \n");
}

Explorator::~Explorator() {
	output_label.close();
	output_stat.close();
}

void Explorator::visitAll() {
	printf(
			"Error!! An implementation must be done to the function visitAll() by a class 'child' of Explorator\n");
}

/********************************** 
 FUNCTION : random_jump

 This function returns which node becomes the new "root",
 the one to where make the "jump" and to continue
 the search of the test purposes.
 The two parameters correspond to the lowest and highets node numbers (IDs)
 which were not visited yet, and that are candidates to the "root" position
 ***********************************/

/* ===== MAIN ===== */

void handler(int sig) {
	// print out all the frames to stderr
	fprintf(stderr, "Error: signal %d:\n", sig);
	CallTrace::print();
}

int main(int argc, char * argv[]) {
	signal(SIGSEGV, handler);   // install our handler

	static const unsigned DEFAULTDEPTH = 20;
	int depthlim = DEFAULTDEPTH;     // maxdepth
	char* sc_file = NULL;  // Stop Conditions File

	enum {
		BFS, DFS
	} traversal = BFS;

	if (argc < 3) {
		fprintf(stderr,
				"\n Usage: %s [-traversal(bfs|dfs) -maxdepth(integer)? -p(test_purposes_file)?]\n\n",
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
	if (traversal == BFS) {
		BfsExplorator* bfs = new BfsExplorator(engine, sc_file);
		bfs->visitAll(depthlim);
	}
	if (traversal == DFS) {
		DfsExplorator* dfs = new DfsExplorator(engine, sc_file);
		dfs->visitAll(depthlim);
	}
	return 0;
}
