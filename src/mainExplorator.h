/*  

 mainExplorator.h : the definition of the functions that belongs to "mainExplorator.C"

 Last modification by Mounir LALLALI mlallali@gmail.com
 02/02/2009

 Main file: mainExplorator.C

 Defines abstract graph exploration

 */

#ifndef __TEMP_H__
#define __TEMP_H__

#include "simulator.h"
#include "state_queue.h"
#include "state_list.h"
#include "state_stack.h"
#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include <execinfo.h>
class CallTrace {
public:
	static void print();
};

/******** EXPLORATOR ***************************/

class Explorator: public IfDriver {

public:
	Explorator(const IfEngine* engine, char* sc_file);
	virtual ~Explorator();
	void readTestPurposes(char* sc_file);
	void printTestPurposes();
	void printPurposes();
	void printOrdPurposes();
	void printPurpose(int i, long int depth);
	void printOrdPurpose(int i, long int depth);
	void saveTestPurposes();
	void savePurposes();
	void saveOrdPurposes();
	void saveStat(short int i);

protected:
	void print_label(long int label_id, IfLabel* label);
	int getTypeSignal(char* type);
	virtual void visitAll();
	void setTestPurposes();
	long int checkTestPurpose(const IfConfig* source, IfLabel* label,
			const IfConfig* target, long int depth);
	long int checkPurpose(const IfConfig* source, IfLabel* label,
			const IfConfig* target, long int depth);
	long int checkOrdPurpose(const IfConfig* source, IfLabel* label,
			const IfConfig* target, long int depth);
	long int checkBoundClock(bool order, const IfConfig *state,
			IfInstance *stateInstance, int ind, long int depth);
	long int checkActiveClock(bool order, IfInstance *state, int ind,
			long int depth);
	long int checkVariable(bool order, IfInstance *state, int ind,
			long int depth);
	long int checkSignal(bool order, IfLabel* label, int ind, long int depth);
	IfInstance* checkProcessInstance(const IfConfig *state,
			char *processInstanceName, long int depth);
	long int checkState(IfInstance *state, char *searchedState, long int depth);
	bool checkParameter(IfLabel* transitionLabel, char* signal_name,
			char* signal_type_name, char* signal_parameter);
	void getClockId(IfInstance *state, char *searchedClock, int *id);
	void getVariableValue(IfInstance *state, char *searchedVariable,
			char value[25]);
	void getParameterValue(IfLabel* label, char* signal_name,
			char* signal_type_name, char parameter[300]);

protected:
	ofstream output_label;
	ofstream output_stat;
	ifstream input_sc;                    //States Format File

	unsigned q_count;                       // state counter
	unsigned t_count;                  // transition counter

	unsigned m_flags;                               // flags
	unsigned m_time;                       // execution time

	StateList output_queue, jump_queue;

	static const unsigned REACHED = 1;
	static const unsigned NumSIGNALS = 10;
	static const unsigned NumSTATES = 10;
	static const unsigned NumCLOCKS = 10;
	static const unsigned NumActiveCLOCKS = 10;
	static const unsigned NumVARIABLES = 10;
	static const unsigned NumPURPOSES = 20;
	static const unsigned VALUE = 25; // the length of variable value
	static const unsigned PARAMETER = 300; // the length of parameter value

	int stateNumber;
	long int label_id;
	int jump_counter;

	/* GLOBAL VARIABLES */

	/* CLOCK */

	typedef struct clockData {
		char* name;
		int bound;
	} ClockData;

	typedef struct activeClockData {
		char* name;
		bool status;
	} ActiveClock;

	typedef ClockData clocksArray[NumCLOCKS];

	typedef activeClockData activeClocksArray[NumActiveCLOCKS];

	typedef struct variableData {
		char* name;
		char value[VALUE];
	} VariableData;

	typedef VariableData variablesArray[NumVARIABLES];

	/* MESSAGES/SIGNALS */
	typedef struct signalData {
		char* name;
		char* type;
		char* parameter;
	} SignalData;

	typedef SignalData signalsArray[NumSIGNALS];

	/* purpose */
	int numTestPurposes;
	int numFoundedTestPurposes;

	int numOrdPurposes;
	int numFoundedOrdPurposes;
	int numPurposes;
	int numFoundedPurposes;

	typedef struct testPurpose {
		bool status;
		bool visited;
		int numBoundClocks;
		int numActiveClocks;
		int numSignals;
		int numVariables;
		long int depth;
		char* process;
		char* source;
		char* target;
		signalsArray signals;
		clocksArray clocks;
		activeClocksArray active_clocks;
		variablesArray variables;
	} Purpose;

	typedef testPurpose purposesArray[NumPURPOSES]; // Set of test purposes
	purposesArray purposes;
	purposesArray ordPurposes;
};

/******************** BFS *************************/

/* 
 *
 * bfs_explorator : breadth-first search exploration
 *
 */

class BfsExplorator: public Explorator {
public:
	BfsExplorator(const IfEngine* engine, char* sc_file);
	virtual ~BfsExplorator() {
	}
	;
	void explore(IfConfig* source, IfLabel* label, IfConfig* target);
	void visitAll(int depthlim);
	StateNode random_jump();

protected:
	long int visit(const IfConfig* state, long int depth);

private:
	StateQueue m_queue;
	stateQNode state_node;
	StateList seq;
	long int raiz;
	long int hit_position;

};

/******************** DFS *************************/

/*
 *
 * dfs_explorator : depth-first search exploration 
 *
 */

class DfsExplorator: public Explorator {

public:
	DfsExplorator(const IfEngine* engine, char* sc_file);
	virtual ~DfsExplorator() {
	}
	;

public:
	void explore(IfConfig* source, IfLabel* label, IfConfig* target);
	void visitAll(int depthlim);

protected:
	long int visit(const IfConfig* state, long int depth,
			long int positionState);

private:
	StateStack m_stack;

	StateNode state_node;
	StateList seq;
	long int raiz;
};

/***** TIME  *********/
class Time: public IfDiscreteTime {

public:
	int print(int i, int bound);
};

#endif // __TEMP_H__
