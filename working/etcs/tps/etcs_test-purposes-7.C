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

	for (i=0; i < numOrdPurposes;i++) 
	{
		ordPurposes[i].status = false;
		ordPurposes[i].visited = false;
		ordPurposes[i].process = NULL;  
		ordPurposes[i].source = NULL;      	
		ordPurposes[i].target = NULL;      	
    		ordPurposes[i].numBoundClocks = 0;
    		ordPurposes[i].numActiveClocks = 0;
    		ordPurposes[i].numSignals = 0;
		ordPurposes[i].numVariables = 0;
		ordPurposes[i].depth = -1;
	}

	purposes[0].numBoundClocks = 1;      
	purposes[0].numSignals = 1;	
	purposes[0].process = "{Train}0";
	purposes[0].source = "moving";
	purposes[0].target = "negotiation";

	signalData signal1 = {"--Timeout TAB","informal", NULL};

	purposes[0].signals[0] = signal1;

	ClockData clock1 = {"c_TAB",5};
	purposes[0].clocks[0] = clock1;

