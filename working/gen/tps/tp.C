
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

	purposes[0].numSignals = 1;
	purposes[0].process = "{o}0";
	purposes[0].source = "s0";
	purposes[0].target = NULL;

	signalData signal1 = {"MA","input", "{1}"};
	//signalData signal2 = {"success","informal",NULL};
	
	purposes[0].signals[0] = signal1;
	//purposes[0].signals[1] = signal2;
