
	numOrdPurposes = 0;
	numPurposes = 1;

	int i;
	for (i=0; i < numPurposes;i++) 
	{
		purposes[i].status = false;
		purposes[i].visited = false;      	
		purposes[i].process = NULL;  
		purposes[i].source = NULL;      	
		purposes[i].target = NULL;  			
		purposes[i].numBoundClocks = 0;
		purposes[i].numActiveClocks = 0;
		purposes[i].numSignals = 0;
		purposes[i].numVariables = 0;
		purposes[i].depth = -1;
	}

	purposes[0].numSignals = 5;
	purposes[0].process = "{PCEPChild}0";
	purposes[0].source = NULL;
	purposes[0].target = NULL;

	signalData signal1 = {"TCP_Data_PCEP_Open_ind","input",NULL};
	signalData signal2 = {"PCEP_Error_ind","output",NULL};
	signalData signal3 = {"TCP_Data_PCEP_Close_req","output",NULL};
	signalData signal4 = {"TCP_Close_req","output",NULL};	
	signalData signal5 = {"--ClearResources","informal",NULL};
	
	purposes[0].signals[0] = signal1;
	purposes[0].signals[1] = signal2;
	purposes[0].signals[2] = signal3;
	purposes[0].signals[3] = signal4;
	purposes[0].signals[4] = signal5;
