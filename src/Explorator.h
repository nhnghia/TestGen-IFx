/*
 * Explorator.h
 *
 *  Created on: 27 juin 2014
 *      Author: nhnghia
 */

#ifndef EXPLORATOR_H_
#define EXPLORATOR_H_

#include "state_queue.h"
#include "state_list.h"
#include "state_stack.h"

#include <stdlib.h>
#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>

#include "TestCase.h"

namespace tsp {

class Explorator: public IfDriver {
public:
	Explorator(const IfEngine* engine);
	virtual ~Explorator();
public:
	virtual void explore(IfConfig* source, IfLabel* label, IfConfig* target);
	virtual void visitAll(int depthlim);
	int numberOfTestCasesGenerated;
	string testCasesFolder;
	bool isProjectTestCases;

public:
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

	void printTestCase();

	int getTypeSignal(char* type);
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
	std::set<unsigned long> testCasesHash;
	int maxDepth;
	int currentDepth;

	TestCase testCase;

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

/***** TIME  *********/
class Time: public IfDiscreteTime {

public:
	int print(int i, int bound);
};


} /* namespace tsp */

#endif /* EXPLORATOR_H_ */
