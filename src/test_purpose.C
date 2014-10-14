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

purposes[0].process = "{Client}0";
purposes[0].source = "s3";
purposes[0].target = "s4";
purposes[0].numVariables = 0;
//VariableData var = {"email2", "0"};
//purposes[0].variables[0] = var;
