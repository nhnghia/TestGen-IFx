/*    
 ManageOutputFiles.C : Manage the output files.

 Last modification by Mounir LALLALI mlallali@gmail.com
 02/02/2009

 Main file: mainExplorator.C
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>

#include <signal.h>
#include "mainExplorator.h"
#include "state_queue.h"
#include "simulator.h"

void Explorator::saveStat(short int i) {

	if (!output_stat) {
		printf("\n #### File 'output.label' not open #### \n");

	} else {
		output_stat << "	Visited states: " << label_id << endl;
		output_stat << "	Number of executed Jumps: " << jump_counter << endl;

		if (i == 1)
			output_stat << "	Test generation success: satisfied test purposes ("
					<< numFoundedTestPurposes << "/" << numTestPurposes << ")"
					<< endl;
		else
			output_stat << "	Test generation fail: satisfied test purposes ("
					<< numFoundedTestPurposes << "/" << numTestPurposes << ")"
					<< endl;
	}
}

void Explorator::saveTestPurposes() {
	int i;
	if (!output_stat) {
		printf("\n >>> File 'output.stat' not open ! \n");
	} else {

		if (numTestPurposes > 0) {
			output_stat << "\tTest Purposes are TP = {";

			for (i = 1; i < numTestPurposes; i++)
				output_stat << "tp" << i << ",";
			output_stat << "tp" << numTestPurposes << "}";

			if (numOrdPurposes > 0) {
				output_stat << " such that ";
				for (i = 1; i < numOrdPurposes; i++)
					output_stat << "tp" << i << " < ";
				output_stat << "tp" << numTestPurposes << endl;
				saveOrdPurposes();
			} else
				output_stat << endl;

			if (numPurposes > 0) {
				savePurposes();
			}

		}
	}
}

void Explorator::savePurposes() {
	int i, j;
	for (i = 0; i < numPurposes; i++) {
		output_stat << "\t  Test Purpose tp" << i + 1 + numOrdPurposes
				<< " is satisfied at Depth " << purposes[i].depth << " :"
				<< endl;
		if (purposes[i].source != NULL)
			output_stat << "\t \t\"Source State = " << purposes[i].source
					<< "\"" << endl;
		if (purposes[i].target != NULL)
			output_stat << "\t \t\"Target State = " << purposes[i].target
					<< "\"" << endl;

		if (purposes[i].numSignals > 0) {
			for (j = 0; j < purposes[i].numSignals; j++) {
				output_stat << "\t \t\"Signal " << purposes[i].signals[j].type
						<< " " << purposes[i].signals[j].name;
				if (purposes[i].signals[j].parameter != NULL)
					output_stat << purposes[i].signals[j].parameter;
				output_stat << "\"" << endl;
			}
		}
		if (purposes[i].numVariables > 0) {
			for (j = 0; j < purposes[i].numVariables; j++) {
				output_stat << "\t \t\"Variable "
						<< purposes[i].variables[j].name << " = "
						<< purposes[i].variables[j].value << "\"" << endl;
			}
		}
		if (purposes[i].numActiveClocks > 0) {
			for (j = 0; j < purposes[i].numActiveClocks; j++) {
				if (purposes[i].active_clocks[j].status == false) {
					output_stat << "\t \t\"Clock "
							<< purposes[i].active_clocks[j].name
							<< " is inactive " << "\"" << endl;
				} else if (purposes[i].active_clocks[j].status == true) {
					output_stat << "\t \t\"Clock "
							<< purposes[i].active_clocks[j].name
							<< " is active " << "\"" << endl;
				}
			}
		}
		if (purposes[i].numBoundClocks > 0) {
			for (j = 0; j < purposes[i].numBoundClocks; j++)
				output_stat << "\t \t\"Clock " << purposes[i].clocks[j].name
						<< " = " << purposes[i].clocks[j].bound << "\"" << endl;
		}
	}
}

void Explorator::saveOrdPurposes() {
	int i, j;
	for (i = 0; i < numOrdPurposes; i++) {
		output_stat << "\t  Test Purpose tp" << i + 1
				<< " is satisfied at Depth " << ordPurposes[i].depth << " :"
				<< endl;

		if (ordPurposes[i].source != NULL)
			output_stat << "\t \t\"Source State = " << ordPurposes[i].source
					<< "\"" << endl;

		if (ordPurposes[i].target != NULL)
			output_stat << "\t \t\"Target State = " << ordPurposes[i].target
					<< "\"" << endl;

		if (ordPurposes[i].numSignals > 0) {
			for (j = 0; j < ordPurposes[i].numSignals; j++) {
				output_stat << "\t \t\"Signal "
						<< ordPurposes[i].signals[j].type << " "
						<< ordPurposes[i].signals[j].name;
				if (ordPurposes[i].signals[j].parameter != NULL)
					output_stat << ordPurposes[i].signals[j].parameter;
				output_stat << "\"" << endl;
			}
		}
		if (ordPurposes[i].numVariables > 0) {
			for (j = 0; j < ordPurposes[i].numVariables; j++) {
				output_stat << "\t \t\"Variable "
						<< ordPurposes[i].variables[j].name << " = "
						<< ordPurposes[i].variables[j].value << "\"" << endl;
			}
		}
		if (ordPurposes[i].numActiveClocks > 0) {
			for (j = 0; j < ordPurposes[i].numActiveClocks; j++) {
				if (ordPurposes[i].active_clocks[j].status == false) {
					output_stat << "\t \t\"Clock "
							<< ordPurposes[i].active_clocks[j].name
							<< " is inactive " << "\"" << endl;
				} else if (ordPurposes[i].active_clocks[j].status == true) {
					output_stat << "\t \t\"Clock "
							<< ordPurposes[i].active_clocks[j].name
							<< " is active " << "\"" << endl;
				}
			}
		}
		if (ordPurposes[i].numBoundClocks > 0) {
			for (j = 0; j < ordPurposes[i].numBoundClocks; j++)
				output_stat << "\t \t\"Clock " << ordPurposes[i].clocks[j].name
						<< " = " << ordPurposes[i].clocks[j].bound << "\""
						<< endl;
		}
	}
}

void Explorator::print_label(long int label_id, IfLabel* label) {
	if (!output_label) {
		printf("\n #### File 'output.label' not open #### \n");
	} else {
		output_label << label_id << ":";
		output_label << label->string() << endl;
	}
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
