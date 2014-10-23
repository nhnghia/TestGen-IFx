/*
 * Explorator.cpp
 *
 *  Created on: 27 juin 2014
 *      Author: nhnghia
 */
#include <algorithm>
#include "Explorator.h"
#include "Tool.h"
#include <regex>
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>
#include <xercesc/dom/DOM.hpp>
#include <xercesc/util/OutOfMemoryException.hpp>
#include <xercesc/framework/XMLFormatter.hpp>
#include <xercesc/framework/LocalFileFormatTarget.hpp>
#include <xercesc/dom/DOMDocument.hpp>
#include <xercesc/dom/DOMImplementation.hpp>
#include <xercesc/dom/DOMImplementationRegistry.hpp>
#include <xercesc/dom/DOMLSSerializer.hpp>
#include <xercesc/dom/DOMLSOutput.hpp>

namespace tsp {

void Explorator::printTestCase(){
	testCase = testCase.optimize();

	if (testCase.size() == 0)
		return;
	//check if exists a test case that is similar

	stringstream ss1;
	testCase.print(ss1);
	string str = ss1.str();
	unsigned long hash = tsp::Tool::hash(str.c_str());
	//cout <<hash <<endl <<str <<endl;
	if (testCasesHash.find(hash) != testCasesHash.end())
		return;

	testCasesHash.insert(hash);


	numberOfTestCasesGenerated ++;
	printf(" \b\r   Number of Test Cases: %d ", numberOfTestCasesGenerated);
	fflush(stdout);

	//return;
	stringstream ss;
	ss << testCasesFolder <<"/" <<(numberOfTestCasesGenerated) <<"_";
	string path = ss.str();


	//global test cases
	string tcFilename(path);
	tcFilename.append("global.tc");

	ofstream out(tcFilename);
	if (out.fail()){
		fprintf(stderr, "\n Error: cannot write test cases to [%s]", testCasesFolder.c_str());
		return;
	}


	testCase.print(out);
	out.close();


	//local test cases
	set<string> partners = testCase.getPartners();
	if (isProjectTestCases)
		for (set<string>::iterator i = partners.begin(); i != partners.end(); i++) {
			string p = *i;

			tcFilename = string(path);
			tcFilename.append(p);
			tcFilename.append(".tc");

			ofstream o(tcFilename);
			TestCase t = testCase.project(p);
			//t.print(cout);
			t = t.optimize();
			t.print(o);
			o.close();
		}
}




Explorator::Explorator(const IfEngine* engine) :
		IfDriver(engine) {

	testCasesFolder = "./";
	maxDepth = 0;
	currentDepth = 0;

	stateNumber = 0;

	srand(static_cast<unsigned>(time(NULL)));
	srand((unsigned) time(0));

}

Explorator::~Explorator() {
}

void Explorator::explore(IfConfig* source, IfLabel* label, IfConfig* target) {
}

void Explorator::visitAll(int depthlim) {
	maxDepth = depthlim;
}

void Explorator::setTestPurposes() {
#include "test_purpose.C"

	numTestPurposes = numPurposes + numOrdPurposes;
	if (numTestPurposes > 0) {
		numFoundedTestPurposes = 0;
		numFoundedOrdPurposes = 0;
		numFoundedPurposes = 0;
	} else {
		cout << endl;
		printf(" Number of Test Purposes at the beggining = %d. \n", 0);
		printf(
				"_________________________________________________________________ \n");
		numFoundedTestPurposes = 0;
		numFoundedOrdPurposes = 0;
		numFoundedPurposes = 0;
		saveTestPurposes();
		exit(1);
	}

	printTestPurposes();
	cout << endl;
	printf(" Number of Test Purposes at the beggining = %d. \n",
			numTestPurposes);
	printf(
			"_________________________________________________________________ \n");
}

/*
 _____________________________________________________________________________
 FUNCTION: printPurpose
 _____________________________________________________________________________
 */

void Explorator::printPurpose(int i, long int depth) {
	int j;

	printf("\n a Hit! - The Test Purpose tp%d is satisfied at Depth %ld:\n",
			i + 1 + numOrdPurposes, purposes[i].depth);
	if (purposes[i].process != NULL)
		printf("\t \t \"Process Instance = %s\"\n", purposes[i].process);
	if (purposes[i].source != NULL)
		printf("\t \t \"Source State = %s\"\n", purposes[i].source);
	if (purposes[i].target != NULL)
		printf("\t \t \"Target State = %s\"\n", purposes[i].target);
	if (purposes[i].numSignals > 0) {
		for (j = 0; j < purposes[i].numSignals; j++) {
			printf("\t  \t \"Signal %s %s", purposes[i].signals[j].type,
					purposes[i].signals[j].name);
			if (purposes[i].signals[j].parameter != NULL)
				printf("%s", purposes[i].signals[j].parameter);
			printf("\"\n");
		}
	}
	if (purposes[i].numVariables > 0) {
		for (j = 0; j < purposes[i].numVariables; j++)
			printf("\t  \t \"Variable %s = %s\"\n",
					purposes[i].variables[j].name,
					purposes[i].variables[j].value);
	}
	if (purposes[i].numActiveClocks > 0) {
		for (j = 0; j < purposes[i].numActiveClocks; j++) {
			if (purposes[i].active_clocks[j].status == false) {
				printf("\t  \t \"Clock %s is inactive\"\n",
						purposes[i].active_clocks[j].name);
			} else if (purposes[i].active_clocks[j].status == true) {
				printf("\t  \t \"Clock %s is active\"\n",
						purposes[i].active_clocks[j].name);
			}
		}
	}
	if (purposes[i].numBoundClocks > 0) {
		for (j = 0; j < purposes[i].numBoundClocks; j++)
			printf("\t  \t \"Clock %s = %d\"\n", purposes[i].clocks[j].name,
					purposes[i].clocks[j].bound);
	}
}

/*
 _____________________________________________________________________________
 FUNCTION: printOrdPurpose
 _____________________________________________________________________________
 */

void Explorator::printOrdPurpose(int i, long int depth) {
	int j;
	printf("\t a Hit! - The Test Purpose tp%d is satisfied at Depth %ld:\n",
			i + 1, ordPurposes[i].depth);

	if (ordPurposes[i].process != NULL)
		printf("\t \t \"Process Instance = %s\"\n", ordPurposes[i].process);

	if (ordPurposes[i].source != NULL)
		printf("\t \t \"Source State = %s\"\n", ordPurposes[i].source);
	if (ordPurposes[i].target != NULL)
		printf("\t \t \"Target State = %s\"\n", ordPurposes[i].target);
	if (ordPurposes[i].numSignals > 0) {
		for (j = 0; j < ordPurposes[i].numSignals; j++) {
			printf("\t  \t \"Signal %s %s", ordPurposes[i].signals[j].type,
					ordPurposes[i].signals[j].name);
			if (ordPurposes[i].signals[j].parameter != NULL)
				printf("%s", ordPurposes[i].signals[j].parameter);
			printf("\"\n");
		}
	}
	if (ordPurposes[i].numVariables > 0) {
		for (j = 0; j < ordPurposes[i].numVariables; j++)
			printf("\t  \t \"Variable %s = %s\"\n",
					ordPurposes[i].variables[j].name,
					ordPurposes[i].variables[j].value);
	}
	if (ordPurposes[i].numActiveClocks > 0) {
		for (j = 0; j < ordPurposes[i].numActiveClocks; j++) {
			if (ordPurposes[i].active_clocks[j].status == false) {
				printf("\t  \t \"Clock %s is inactive\"\n",
						ordPurposes[i].active_clocks[j].name);
			} else if (ordPurposes[i].active_clocks[j].status == true) {
				printf("\t  \t \"Clock %s is active\"\n",
						ordPurposes[i].active_clocks[j].name);
			}
		}
	}
	if (ordPurposes[i].numBoundClocks > 0) {
		for (j = 0; j < ordPurposes[i].numBoundClocks; j++)
			printf("\t  \t \"Clock %s = %d\"\n", ordPurposes[i].clocks[j].name,
					ordPurposes[i].clocks[j].bound);
	}
}

/*
 _____________________________________________________________________________
 FUNCTION: printTestPurposes
 _____________________________________________________________________________
 */

void Explorator::printTestPurposes() {
	int i;
	if (numTestPurposes > 0) {
		printf(" Test Purposes TP = {");

		for (i = 1; i < numTestPurposes; i++)
			printf("tp%d,", i);
		printf("tp%d}", numTestPurposes);

		if (numOrdPurposes > 0) {
			printf(" such that ");
			for (i = 1; i < numOrdPurposes; i++)
				printf("tp%d < ", i);
			printf("tp%d\n\n", numOrdPurposes);
			printOrdPurposes();

		} else
			printf("\n\n");

		if (numPurposes > 0) {
			printPurposes();
		}
	}
}
/*
 _____________________________________________________________________________
 FUNCTION: printOrdPurposes
 ____________________________________________________________________________
 */

void Explorator::printOrdPurposes() {
	int i, j;
	for (i = 0; i < numOrdPurposes; i++) {
		printf("\t Test Purpose tp%d: \n", i + 1);

		if (ordPurposes[i].process != NULL)
			printf("\t \t \"Process Instance = %s\"\n", ordPurposes[i].process);

		if (ordPurposes[i].source != NULL)
			printf("\t  \t \"Source State = %s\"\n", ordPurposes[i].source);
		if (ordPurposes[i].target != NULL)
			printf("\t \t \"Target State = %s\"\n", ordPurposes[i].target);
		if (ordPurposes[i].numSignals > 0) {
			for (j = 0; j < ordPurposes[i].numSignals; j++) {
				printf("\t  \t \"Signal %s %s", ordPurposes[i].signals[j].type,
						ordPurposes[i].signals[j].name);
				if (ordPurposes[i].signals[j].parameter != NULL)
					printf("%s", ordPurposes[i].signals[j].parameter);
				printf("\"\n");
			}
		}
		if (ordPurposes[i].numVariables > 0) {
			for (j = 0; j < ordPurposes[i].numVariables; j++) {
				printf("\t  \t \"Variable %s = %s\"\n",
						ordPurposes[i].variables[j].name,
						ordPurposes[i].variables[j].value);
			}
		}
		if (ordPurposes[i].numActiveClocks > 0) {
			for (j = 0; j < ordPurposes[i].numActiveClocks; j++) {
				if (ordPurposes[i].active_clocks[j].status == false) {
					printf("\t  \t \"Clock %s is inactive\"\n",
							ordPurposes[i].active_clocks[j].name);
				} else if (ordPurposes[i].active_clocks[j].status == true) {
					printf("\t  \t \"Clock %s is active\"\n",
							ordPurposes[i].active_clocks[j].name);
				}
			}
		}
		if (ordPurposes[i].numBoundClocks > 0) {
			for (j = 0; j < ordPurposes[i].numBoundClocks; j++)
				printf("\t  \t \"Clock %s = %d\"\n",
						ordPurposes[i].clocks[j].name,
						ordPurposes[i].clocks[j].bound);
		}
	}
}

/*
 _____________________________________________________________________________
 FUNCTION: printPurposes
 _____________________________________________________________________________
 */

void Explorator::printPurposes() {

	int i, j;
	for (i = 0; i < numPurposes; i++) {
		printf("\t Test Purpose tp%d: \n", i + 1 + numOrdPurposes);
		if (purposes[i].process != NULL)
			printf("\t \t \"Process Instance = %s\"\n", purposes[i].process);
		if (purposes[i].source != NULL)
			printf("\t  \t \"Source State = %s\"\n", purposes[i].source);
		if (purposes[i].target != NULL)
			printf("\t \t \"Target State = %s\"\n", purposes[i].target);
		if (purposes[i].numSignals > 0) {
			for (j = 0; j < purposes[i].numSignals; j++) {
				printf("\t  \t \"Signal %s %s", purposes[i].signals[j].type,
						purposes[i].signals[j].name);
				if (purposes[i].signals[j].parameter != NULL)
					printf("%s", purposes[i].signals[j].parameter);
				printf("\"\n");
			}
		}
		if (purposes[i].numVariables > 0) {
			for (j = 0; j < purposes[i].numVariables; j++) {
				printf("\t  \t \"Variable %s = %s\"\n",
						purposes[i].variables[j].name,
						purposes[i].variables[j].value);
			}
		}
		if (purposes[i].numActiveClocks > 0) {
			for (j = 0; j < purposes[i].numActiveClocks; j++) {
				if (purposes[i].active_clocks[j].status == false) {
					printf("\t  \t \"Clock %s is inactive\"\n",
							purposes[i].active_clocks[j].name);
				} else if (purposes[i].active_clocks[j].status == true) {
					printf("\t  \t \"Clock %s is active\"\n",
							purposes[i].active_clocks[j].name);
				}
			}
		}
		if (purposes[i].numBoundClocks > 0) {
			for (j = 0; j < purposes[i].numBoundClocks; j++)
				printf("\t  \t \"Clock %s = %d\"\n", purposes[i].clocks[j].name,
						purposes[i].clocks[j].bound);
		}
	}
}

/*
 _____________________________________________________________________________
 FUNCTION: readTestPurposes
 _____________________________________________________________________________
 */

void Explorator::readTestPurposes(char* sc_file) {
	numTestPurposes = 0;

	input_sc.open(sc_file, ios_base::in);
	if (!input_sc) {
		printf("\n #### Test Purposes File not open #### \n");
	} else {
		while (!input_sc.eof()) {
			char line[256];
			input_sc.getline(line, sizeof(line));
			printf("ligne = %s\n", line);
		}
	}
	input_sc.close();
}

/*
 _____________________________________________________________________________
 FUNCTION: checkPurpose
 Verify the Test Purpose
 _____________________________________________________________________________
 */

long int Explorator::checkTestPurpose(const IfConfig* sourceState,
		IfLabel* transitionLabel, const IfConfig* targetState, long int depth) {
	long int hitDepth = -1;
	long int hitDepth1 = -1;
	long int hitDepth2 = -1;

	if (numFoundedTestPurposes < numTestPurposes) {
		if (numFoundedOrdPurposes < numOrdPurposes)
			hitDepth1 = checkOrdPurpose(sourceState, transitionLabel,
					targetState, depth);

		if (numFoundedPurposes < numPurposes)
			hitDepth2 = checkPurpose(sourceState, transitionLabel, targetState,
					depth);
	}

	if (hitDepth1 == -2 || hitDepth2 == -2)
		hitDepth = -2;

	if (hitDepth1 > -1 || hitDepth2 > -1)
		hitDepth = depth;

	return hitDepth;
}

/*
 _____________________________________________________________________________
 FUNCTION: checkOrdPurpose
 _____________________________________________________________________________
 */

long int Explorator::checkOrdPurpose(const IfConfig* sourceState,
		IfLabel* transitionLabel, const IfConfig* targetState, long int depth) {
	IfInstance *sourceStateInstance;
	IfInstance *targetStateInstance;
	long int hitDepth = -1;
	long int tmpDepth = -1;
	int k = 0;
	bool hit = true;

	while (k < numOrdPurposes && ordPurposes[k].status == true)
		k++;
	if (k < numOrdPurposes) {

		if (hit && ordPurposes[k].numSignals > 0) {
			tmpDepth = checkSignal(true, transitionLabel, k, depth);
			if (tmpDepth == -1)
				hit = false;
		}

		if (hit && ordPurposes[k].process != NULL) {
			sourceStateInstance = checkProcessInstance(sourceState,
					ordPurposes[k].process, depth);
			if (sourceStateInstance == NULL) {
				hit = false;
			} else {
				tmpDepth = depth;
			}
		} else
			hit = false;

		if (hit && ordPurposes[k].source != NULL) {
			tmpDepth = checkState(sourceStateInstance, ordPurposes[k].source,
					depth);
			if (tmpDepth == -1)
				hit = false;
		}

		if (hit && ordPurposes[k].target != NULL) {
			targetStateInstance = checkProcessInstance(targetState,
					ordPurposes[k].process, depth);
			if (targetStateInstance != NULL) {
				tmpDepth = checkState(targetStateInstance,
						ordPurposes[k].target, depth);
				if (tmpDepth == -1)
					hit = false;
			} else
				hit = false;
		}

		if (hit && ordPurposes[k].numVariables > 0) {
			tmpDepth = checkVariable(true, sourceStateInstance, k, depth);
			if (tmpDepth == -1)
				hit = false;
		}

		if (hit && ordPurposes[k].numActiveClocks > 0) {
			tmpDepth = checkActiveClock(true, sourceStateInstance, k, depth);
			if (tmpDepth == -1)
				hit = false;
		}

		if (hit && ordPurposes[k].numBoundClocks > 0) {
			tmpDepth = checkBoundClock(true, sourceState, sourceStateInstance,
					k, depth);
			if (tmpDepth == -1)
				hit = false;
		}

		if (tmpDepth > -1 && hit) {
			ordPurposes[k].depth = depth;
			printOrdPurpose(k, depth);
			numFoundedTestPurposes++;
			numFoundedOrdPurposes++;

			if (numFoundedTestPurposes == numTestPurposes) {
				printf(
						" Success! - All Test Purposes are Satisfied (%d/%d). \n\n",
						numFoundedTestPurposes, numTestPurposes);
				return -2; // -2 for exit
			} else {
				hitDepth = depth;
				cout << endl;
				printf(" Number of Satisfied Test Purposes = %d/%d.  \n",
						numFoundedTestPurposes, numTestPurposes);
				ordPurposes[k].status = true;
				return hitDepth;
			}
		}
	}
	return hitDepth;
}

/*
 _____________________________________________________________________________
 FUNCTION: checkPurpose
 _____________________________________________________________________________
 */

long int Explorator::checkPurpose(const IfConfig* sourceState,
		IfLabel* transitionLabel, const IfConfig* targetState, long int depth) {
	long int hitDepth = -1;
	long int tmpDepth = -1;
	IfInstance *sourceStateInstance = NULL;
	IfInstance *targetStateInstance = NULL;
	int k = 0;
	int i;
	bool hit;
//cout <<"=====================================================" <<endl;
//	cout <<endl <<"---" <<endl <<sourceState->string() <<"---" <<endl <<targetState->string() <<endl <<"---" <<endl;

	for (i = 0; i < numPurposes; i++)
		purposes[i].visited = false;

	while (k < numPurposes) {

		hit = true;

		while (k < numPurposes
				&& (purposes[k].visited == true || purposes[k].status == true))
			k++;

		if (k < numPurposes) {

			if (hit && purposes[k].numSignals > 0) {
				tmpDepth = checkSignal(false, transitionLabel, k, depth);
				if (tmpDepth == -1)
					hit = false;
			}
			if (hit && purposes[k].process != NULL) {
//cout <<"process " <<endl;
				sourceStateInstance = checkProcessInstance(sourceState,
						purposes[k].process, depth);
				if (sourceStateInstance == NULL) {
					hit = false;
				} else {
					tmpDepth = depth;
				}
			} else
				hit = false;

			if (hit && purposes[k].source != NULL && sourceStateInstance != NULL) {
//cout <<"===source " <<purposes[k].source <<endl;
				tmpDepth = checkState(sourceStateInstance, purposes[k].source,
						depth);
				if (tmpDepth == -1)
					hit = false;
			}

			if (hit && purposes[k].target != NULL) {
//cout <<"===target " <<purposes[k].target <<endl;

				targetStateInstance = checkProcessInstance(targetState,
						purposes[k].process, depth);

				if (targetStateInstance != NULL) {
					tmpDepth = checkState(targetStateInstance,
							purposes[k].target, depth);
					if (tmpDepth == -1)
						hit = false;
				} else
					hit = false;

			}

			if (hit && purposes[k].numVariables > 0)
			{
				tmpDepth = checkVariable(false, sourceStateInstance, k, depth);
				if (tmpDepth == -1)
					hit = false;
			}

			if (hit && purposes[k].numActiveClocks > 0) {
				tmpDepth = checkActiveClock(false, sourceStateInstance, k,
						depth);
				if (tmpDepth == -1)
					hit = false;
			}

			if (hit && purposes[k].numBoundClocks > 0) {
				tmpDepth = checkBoundClock(false, sourceState,
						sourceStateInstance, k, depth);
				if (tmpDepth == -1)
					hit = false;
			}

			if (tmpDepth > -1 && hit) {
				purposes[k].depth = depth;
				printPurpose(k, depth);
				numFoundedTestPurposes++;
				numFoundedPurposes++;

				if (numFoundedTestPurposes == numTestPurposes) {
					printf(
							"_________________________________________________________________ \n");
					printf(
							" Success! - All Test Purposes are Satisfied (%d/%d). \n\n",
							numFoundedTestPurposes, numTestPurposes);
					return -2; // -2 for exit
				} else {
					if (hitDepth == -1)
						hitDepth = depth;
					cout << endl;
					printf(" Number of Satisfied Test Purposes = %d/%d.  \n",
							numFoundedTestPurposes, numTestPurposes);
					printf(
							"_________________________________________________________________ \n");
					purposes[k].status = true;

					if (numFoundedPurposes == numPurposes)
						return hitDepth;
				}
			}
			purposes[k].visited = true;
			while (k < numPurposes
					&& (purposes[k].visited == true
							|| purposes[k].status == true))
				k++;
		}
	}
	return hitDepth;
}

/*
 _____________________________________________________________________________
 FUNCTION: checkParameter
 Verify signal parameters
 _____________________________________________________________________________
 */

char *str_sub(const char *s, unsigned int start, unsigned int end) {
	char *new_s = NULL;

	if (s != NULL && start <= end) {
		new_s = (char *) malloc(sizeof(*new_s) * (end - start + 2));
		if (new_s != NULL) {
			unsigned int i;

			for (i = start; i <= end; i++) {
				new_s[i - start] = s[i];
			}
			new_s[i - start] = '\0';
		} else
			exit(EXIT_FAILURE);
	}
	return new_s;
}

char *str_sub_bis(const char *s, unsigned int start) {
	char *new_s = NULL;

	if (s != NULL) {
		new_s = (char *) malloc(sizeof(*new_s) * 40);
		if (new_s != NULL) {
			unsigned int i = start;
			char * c = str_sub(s, i, i);
			while (strcmp(c, ",") != 0 && strcmp(c, "{") != 0
					&& strcmp(c, "}") != 0) {
				new_s[i - start] = s[i];
				i++;
				c = str_sub(s, i, i);
			}
			new_s[i - start] = '\0';
		} else
			exit(EXIT_FAILURE);
	}
	return new_s;
}

bool Explorator::checkParameter(IfLabel* label, char* signal_name,
		char* signal_type_name, char* signal_parameter) {
	char signalParameter[PARAMETER];
	unsigned int i = 0;
	unsigned int j = 0;
	char *c1;
	char *c2;

	getParameterValue(label, signal_name, signal_type_name, signalParameter);
	if (signalParameter != NULL) {
		if (strcmp(signal_parameter, signalParameter) == 0) {
			return true;
		} else {
			unsigned int l1 = strlen(signal_parameter);
			unsigned int l2 = strlen(signalParameter);
			while (i < l1 && j < l2) {
				char* tmpc1 = str_sub(signal_parameter, i, i);
				char* tmpc2 = str_sub(signalParameter, j, j);

				if ((strcmp(tmpc1, ",") != 0) && (strcmp(tmpc1, "}") != 0)
						&& (strcmp(tmpc1, "{") != 0)
						&& (strcmp(tmpc1, "_") != 0))
					c1 = str_sub_bis(signal_parameter, i);
				else
					c1 = str_sub(signal_parameter, i, i);

				if ((strcmp(tmpc2, ",") != 0) && (strcmp(tmpc2, "}") != 0)
						&& (strcmp(tmpc2, "{") != 0))
					c2 = str_sub_bis(signalParameter, j);
				else
					c2 = str_sub(signalParameter, j, j);

				if (strcmp(c1, c2) == 0) {
					i = i + strlen(c1);
					j = j + strlen(c2);
					free(c1);
					free(c2);

				} else if ((strcmp(c1, "_") == 0) && (strcmp(c2, "}") != 0)
						&& (strcmp(c2, "{") != 0) && (strcmp(c2, ",") != 0)) {
					i = i + strlen(c1);
					j = j + strlen(c2);
					free(c1);
					free(c2);
				} else {
					free(c1);
					free(c2);
					return false;
				}
			}
			if (i == l1 && j == l2) {
				return true;
			} else
				return false;
		}
	} else
		return false;
}

void Explorator::getParameterValue(IfLabel* label, char* signal_name,
		char* signal_type_name, char parameter[PARAMETER]) {

	int n = label->getLength();
	IfEvent *ev;
	string param = "";
	string signalName = string(signal_name);

	for (int i=0; i<n; i++){
		ev = label->getAt(i);
		if (ev->getKind() == getTypeSignal(signal_type_name)){
			string str = ev->getValue();	//Submit{p1={distance=3, speed=1},p2=7}

			if (str.compare(0, signalName.size(), signalName) != 0)
				continue;
			//extract parameters "{p1={distance=3, speed=1},p2=7}" to "{{distance=3, speed=1},7}"

			str = str.substr(signalName.size()); //p1={distance=3, speed=1},p2=7}
			//str = p1={distance=1, speed=2},p2=3
			//remove p1=, p2= .. from label
			std::regex exp ("p(\\d+)=");
			str = std::regex_replace(str, exp, "");

			//str = {distance=1, speed=2},3
			//remove distance=, speed=, ..
			std::regex exp2("(\\w+)=");
			str = std::regex_replace(str, exp2, "");
			param = str;
		}
	}

	strcpy(parameter, param.c_str());
}

/*
 _____________________________________________________________________________
 FUNCTION: checkActiveClock
 Verify a set of Time Conditions : active or inactive condition
 _____________________________________________________________________________
 */

long int Explorator::checkActiveClock(bool order, IfInstance *state, int ind,
		long int depth) {
	long int hitDepth = -1;
	int i = 0;
	int numActiveClocks;
	char *clock_name;
	bool clock_status;

	if (order)
		numActiveClocks = ordPurposes[ind].numActiveClocks;
	else
		numActiveClocks = purposes[ind].numActiveClocks;

	bool hit = true;
	int clock_id = -2;

//cout <<"number of clock " <<numActiveClocks <<endl;

	while (hit && i < numActiveClocks) {
		if (order) {
			clock_name = ordPurposes[ind].active_clocks[i].name;
			clock_status = ordPurposes[ind].active_clocks[i].status;
		} else {
			clock_name = purposes[ind].active_clocks[i].name;
			clock_status = purposes[ind].active_clocks[i].status;
		}

		if (clock_name != NULL) {
			getClockId(state, clock_name, &clock_id);
			if (clock_id == -1 && clock_status == false)
				hit = true;
			else if (clock_id == -1 && clock_status == true)
				hit = false;
			else if (clock_id > 0 && clock_status == true)
				hit = true;
			else if (clock_id > 0 && clock_status == false)
				hit = false;
		} else
			hit = false;
		i++;
	}
	if (hit)
		hitDepth = depth;
	return hitDepth;
}

/*
 _____________________________________________________________________________
 FUNCTION: checkBoundClock
 Verify a set of Time Conditions
 _____________________________________________________________________________
 */

long int Explorator::checkBoundClock(bool order, const IfConfig *state,
		IfInstance *stateInstance, int ind, long int depth) {
	int j, n;
	long int hitDepth = -1;
	int i = 0;
	int numBoundClocks;

	if (order)
		numBoundClocks = ordPurposes[ind].numBoundClocks;
	else
		numBoundClocks = purposes[ind].numBoundClocks;

	bool hit = true;
	bool tmpHit = false;
	IfTime* t = state->getTime();
	int clock_id = -2;

	if (t != NULL) {
		Time *t1 = (Time *) t;
		while (hit && i < numBoundClocks) {
			char *clock_name;
			int clock_bound;
			if (order) {
				clock_name = ordPurposes[ind].clocks[i].name;
				clock_bound = ordPurposes[ind].clocks[i].bound;
			} else {
				clock_name = purposes[ind].clocks[i].name;
				clock_bound = purposes[ind].clocks[i].bound;
			}
			if (clock_name != NULL && clock_bound >= 0) {
				getClockId(stateInstance, clock_name, &clock_id);
				if (clock_id > 0) {
					n = t->dimension();
					j = 1;
					tmpHit = false;
					while (!tmpHit && j <= n) {
						if (j == clock_id) {
							if ((t1->print(j, clock_bound)) == 1) {
								tmpHit = true;
							}
						}
						j++;
					}
					if (tmpHit == false)
						hit = false;
				} else
					hit = false;
			}
			i++;
		}
	}
	if (hit)
		hitDepth = depth;
	return hitDepth;
}

/*
 _____________________________________________________________________________
 FUNCTION: checkVariable
 Verify a set of Variable Conditions
 _____________________________________________________________________________
 */

long int Explorator::checkVariable(bool order, IfInstance *state, int ind,
		long int depth) {
	long int hitDepth = -1;

	if (state == NULL)
			return hitDepth;

	int i = 0;
	int numVariables;
	bool hit = true;
	bool tmpHit = false;
	char variableValue[VALUE];
	char *variable_name;
	char *variable_value;

	if (order)
		numVariables = ordPurposes[ind].numVariables;
	else
		numVariables = purposes[ind].numVariables;

	while (hit && i < numVariables) {
		if (order) {
			variable_name = ordPurposes[ind].variables[i].name;
			variable_value = ordPurposes[ind].variables[i].value;
		} else {
			variable_name = purposes[ind].variables[i].name;
			variable_value = purposes[ind].variables[i].value;
		}
		if (variable_name != NULL) {

			tmpHit = false;
			if (variable_value != NULL) {
				getVariableValue(state, variable_name, variableValue);
				if (strcmp(variable_value, variableValue) == 0)
					tmpHit = true;
			}
			if (tmpHit == false)
				hit = false;
		}
		i++;
	}
	if (hit)
		hitDepth = depth;
	return hitDepth;

}
/*
 _____________________________________________________________________________
 FUNCTION: checkSignal
 Verify a set of Signal Conditions
 _____________________________________________________________________________
 */

long int Explorator::checkSignal(bool order, IfLabel* label, int ind,
		long int depth) {

	int signalType, j;
	int lengthLabel, lengthSignal;
	char *signalName;
	IfEvent *signal;
	int numSignals;
	char *signal_name;
	char *signal_parameter;
	int signal_type;
	char* signal_type_name;
	int i = 0;
	long int hitDepth = -1;
	bool hit = true;
	bool tmpHit = false;

	if (order)
		numSignals = ordPurposes[ind].numSignals;
	else
		numSignals = purposes[ind].numSignals;

	lengthLabel = label->getLength();
	while (hit && i < numSignals) {
		if (order) {
			signal_name = ordPurposes[ind].signals[i].name;
			signal_type = getTypeSignal(ordPurposes[ind].signals[i].type);
			signal_type_name = ordPurposes[ind].signals[i].type;
			signal_parameter = ordPurposes[ind].signals[i].parameter;
		} else {
			signal_name = purposes[ind].signals[i].name;
			signal_type = getTypeSignal(purposes[ind].signals[i].type);
			signal_type_name = purposes[ind].signals[i].type;
			signal_parameter = purposes[ind].signals[i].parameter;
		}
		if (signal_name != NULL) {
			tmpHit = false;
			j = 0;
			while (!tmpHit && j < lengthLabel) {
				signal = label->getAt(j);
				signalType = signal->getKind();
				if (signalType == signal_type) {
					signalName = signal->getValue();
					lengthSignal = strlen(signal_name);
					if ((strncmp(signalName, signal_name, lengthSignal)) == 0) {
						if (signal_parameter != NULL) {
							if (checkParameter(label, signal_name,
									signal_type_name, signal_parameter))
								tmpHit = true;
						} else
							tmpHit = true;
					}
				}
				j++;
			}
			if (tmpHit == false)
				hit = false;
		}
		i++;
	}
	if (hit)
		hitDepth = depth;
	return hitDepth;
}

/**
 _____________________________________________________________________________
 FUNCTION: checkProcessInstance
 Verify a Process Instance Condition: name and id
 _____________________________________________________________________________
 */

IfInstance* Explorator::checkProcessInstance(const IfConfig *state,
		char* processInstanceName, long int depth) {

/* tsp::Tool::ifObject2Xml(state->getAt(j)->getAt(i)
<IfInstance type="RBC_to_OBU" >
</IfInstance>

<IfInstance type="OBU_to_RBC" >
</IfInstance>

<IfInstance type="OBU" state="top:TEMP" >
<var>
<OBU_var>
<m><MovementAuthority>
<distance><integer value='0' /></distance><speed><integer value='0' /></speed></MovementAuthority>
</m><v><integer value='0' /></v><c0><clock id='-1' /></c0><c><clock id='-1' /></c><l><integer value='0' /></l><rbc><pid name='RBC' no='0' /></rbc></OBU_var>
</var>
<par>
<void/></par>
</IfInstance>
 */

	string s;
	int l = 0;
	int i = 0;
	int j = 0;

	if (processInstanceName == NULL)
		return NULL;

	struct IfConfig::Chunk *c1 = state->getAt(j);
	while (c1 != NULL) {
		l = c1->getLength();
		while (i < l) {
			IfInstance* c2 = c1->getAt(i);
			if (c2 == NULL)
				continue;

			//cout << tsp::Tool::ifObject2Xml(c2) <<endl;
			string txt = c2->string();
			//cout <<"----"<<txt <<"----"<<endl;
			vector<string> el = Tool::split(txt, '\t');

			//for (string procname : el){
			string procname = el.at(0);
				if (procname.compare(processInstanceName) == 0){
					//cout <<"checkprocess" <<procname <<endl;
					return c2;
				}
			//}
			i++;
		}
		j++;
		c1 = state->getAt(j);
		i = 0;
	}
	return NULL;
}

/*
 _____________________________________________________________________________
 FUNCTION: checkState
 Verify a State Condition : source or target of transition
 _____________________________________________________________________________
 */

long int Explorator::checkState(IfInstance *state, char* searchedState,
		long int depth) {
	if (searchedState == NULL || state == NULL)
		return -1;

/*
 * tsp::Tool::ifObject2Xml(state)
 <IfInstance type="OBU" state="top:TEMP">
	<var>
		<OBU_var>
			<m>
				<MovementAuthority>
					<distance>
						<integer value="0"/>
					</distance>
					<speed>
						<integer value="0"/>
					</speed>
				</MovementAuthority>
			</m>
			<v>
				<integer value="0"/>
			</v>
			<c0>
				<clock id="-1"/>
			</c0>
			<c>
				<clock id="-1"/>
			</c>
			<l>
				<integer value="1"/>
			</l>
			<rbc>
				<pid name="RBC" no="0"/>
			</rbc>
		</OBU_var>
	</var>
	<par>
		<void/>
	</par>
</IfInstance>
 */

	DOMDocument *doc = tsp::Tool::parserXml(tsp::Tool::ifObject2Xml(state));
	if (doc == NULL)
		return -1;

	string s = tsp::Tool::getXmlAttributeValue(doc, "state");
	//s = top:s0 ==> get s0

	if (s.find(':') != std::string::npos)
		s = tsp::Tool::split(s, ':').at(1);
//cout <<"checkState " << s <<"--" << searchedState <<endl;
	if (s.compare(string(searchedState)) == 0)
		return depth;
	return -1;
}

/*
 _____________________________________________________________________________
 FUNCTION: getVariableValue
 Get dynamically the value of a variable
 _____________________________________________________________________________
 */

void Explorator::getVariableValue(IfInstance *state, char *searchedVariable,
		char value[VALUE]) {
	char *s = "";
	strcpy(value, s);

	if (state == NULL)
		return;

	DOMDocument *doc = tsp::Tool::parserXml(tsp::Tool::ifObject2Xml(state));
	if (doc == NULL)
		return;

	string varName(searchedVariable);

	vector<string> varNames = tsp::Tool::split(varName, '.');

	DOMNodeList* list = doc->getElementsByTagName(
			XMLString::transcode(varNames[0].c_str()));
	if (list == NULL)
		return;

	DOMNode *node = list->item(0);	//<x><integer value="0"/></x>
	if (node == NULL)
		return;

	//cout <<tsp::Tool::xmlNode2String(node) <<endl;
	//eg m.speed
	int n = varNames.size();
	for (int i=1; i<n; i++){
		node = tsp::Tool::getXmlNodeByTagName(node, varNames.at(i));
		if (node == NULL)
			return;
	}



	string str = tsp::Tool::getXmlAttributeValue(node, "value");
	strcpy(value, str.c_str());

	//cout <<varName <<" = " <<str <<endl;
}

/*
 _____________________________________________________________________________
 FUNCTION: getClockId
 Get dynamically the id of a clock
 _____________________________________________________________________________
 */

void Explorator::getClockId(IfInstance *state, char *searchedClock, int *id) {
	if (state == NULL)
		return;

	DOMDocument *doc = tsp::Tool::parserXml(tsp::Tool::ifObject2Xml(state));
	if (doc == NULL)
		return;

	DOMNodeList* list = doc->getElementsByTagName(XMLString::transcode(searchedClock));
	if (list == NULL)
		return;

	DOMNode *node = list->item(0);	//<x><integer value="0"/></x>
	if (node == NULL)
		return;

	string str = tsp::Tool::getXmlAttributeValue(node, "id");
	*id = atoi(str.c_str());
	//cout <<*id <<endl;
	/*
	int d = -1;
	FILE *f1, *f2;
	state->printXML(cout);
	 {
		//if ((state->getState())!= NULL)
		//if ((getState(state)) != NULL)
		{
			f1 = fopen("output.xml", "a");
			if (f1 == NULL) {
				cerr << "cannot open output.xml !" << endl;
			} else {
				//nghia
				//state->xmlize(f1);
				printf("NGHIA 996");
				fclose(f1);

				char commande[200];
				sprintf(commande, "$TestGenIF/lib/get-clock-id.sh %s",
						searchedClock);
				system(commande);

				f2 = fopen("output.id", "r");
				if (f2 == NULL) {
					cerr << "cannot open output.id !" << endl;
				} else {
					fscanf(f2, "%d", &d);
					fclose(f2);
					*id = d;
				}
			}
		}
	}*/
}

/*
 _____________________________________________________________________________
 FUNCTION: getTypeSignal
 Get the type of a signal
 _____________________________________________________________________________
 */

int Explorator::getTypeSignal(char* type) {
	if (strcmp(type, "skip") == 0)
		return IfEvent::SKIP;
	else if (strcmp(type, "informal") == 0)
		return IfEvent::INFORMAL;
	else if (strcmp(type, "task") == 0)
		return IfEvent::TASK;
	else if (strcmp(type, "set") == 0)
		return IfEvent::SET;
	else if (strcmp(type, "reset") == 0)
		return IfEvent::RESET;
	else if (strcmp(type, "input") == 0)
		return IfEvent::INPUT;
	else if (strcmp(type, "output") == 0)
		return IfEvent::OUTPUT;
	else if (strcmp(type, "call") == 0)
		return IfEvent::CALL;
	else if (strcmp(type, "fork") == 0)
		return IfEvent::FORK;
	else if (strcmp(type, "kill") == 0)
		return IfEvent::KILL;
	else if (strcmp(type, "tick") == 0)
		return IfEvent::TICK;
	else if (strcmp(type, "deliver") == 0)
		return IfEvent::DELIVER;
	else if (strcmp(type, "import") == 0)
		return IfEvent::IMPORT;
	else
		return -1;
}

void Explorator::saveStat(short int i) {


}

void Explorator::saveTestPurposes() {

}

void Explorator::savePurposes() {

}

void Explorator::saveOrdPurposes() {

}


int Time::print(int i, int bound) {
	if (bound != -1) {
		if ((m_values.getAt(i) == bound)) {
			bound = -1;
			return (1);
		} else
			return (0);
	} else
		//it means that we are only interested in get the time of this function
		return (m_values.getAt(i));
}

} /* namespace tsp */
