
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
	purposes[0].process = "{server}0";
	purposes[0].source = NULL;
	purposes[0].target = NULL;

	signalData signal0 = {"Report","output","{0}"};
	
	purposes[0].signals[0] = signal0;

	ClockData clock1 = {"c",5};
	purposes[0].clocks[0] = clock1;

	activeClockData clock2 = {"c", false};
	purposes[0].active_clocks[0] = clock2;

	VariableData var = {"x", "3"};
	purposes[0].variables[0] = var;
