/**
 * Since partners of all inputs of an IF process always assign to environment by IF simulator.
 * However, in TestGen-IFx, we need to distinguish an input that comes from the environment or from another process.
 * This is done only based on the signalroute in IF description file.
 * This program will extract the set of signalroute, and their attached signals
 */

#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <fstream>
#include <string>
#include <algorithm>

#include "model.h"



using namespace std;

/**
 * This just is a way to look into protected variables of IfSignalroute
 */
class Signalroute : public IfSignalroute{
	public:
	char *getFromName(){
		return m_pFromName;
	}
	char *getToName(){
		return m_pToName;
	}
};


/**
* truck technique
* I get error when standard types are not declared. I don't understand why
* So I copy the IF file to a temporary file, then insert the definition of these types
*  type integer = range 1..1;
*  type pid = range 1..1;
*  type boolean = range 0..1;
*  type clock = range 0..1;
*/
FILE* copy(FILE *src){
	long lSize;
	char * buffer;
	size_t result;

	// obtain file size:
	fseek(src, 0, SEEK_END);
	lSize = ftell(src);
	rewind (src);

	// allocate memory to contain the whole file:
	buffer = (char*) malloc(sizeof(char) * lSize);
	if (buffer == NULL) {
		fputs("Memory error", stderr);
		exit(2);
	}

	// copy the file into the buffer:
	result = fread(buffer, 1, lSize, src);
	if (result != lSize) {
		fputs("Reading error", stderr);
		exit(3);
	}
	string str = string(buffer);
	int d = str.find("system ");
	if (d != str.npos){
		d = str.find(';', d);	//find ; after system
		str.replace(d, 1, ";type integer = range 1..1;type pid = range 1..1;type boolean = range 0..1;type clock = range 0..1;");
	}
	FILE *des = tmpfile();
	fwrite(str.c_str(), sizeof(char), str.length(),des);
	fflush(des);
	rewind(des);
	return des;
}


int main(int argc, char * argv[]) {

  if (argc != 2 && argc != 3) {
    fprintf(stderr, "\n Usage: %s fileName",argv[0]);
	 fprintf(stderr, "\n\n");
    return 0;
  }

  FILE *file;
  file = fopen(argv[1], "r");
  if (file == NULL){
	  fprintf(stderr, "Cannot open file: %s\n", argv[1]);
	  return 0;
  }

  file = copy(file);


  IfSystemEntity *system = Load(file, NULL, 0);
  IfList<IfSignalroute> *signalroutes = system->GetSignalroutes();
  int n = signalroutes->GetCount();


  //file name is the same with the one in Event.cpp
  ofstream out("/tmp/if-signalroute.XXXXXX");
  if (out.fail()){
	  cout <<endl <<"Error: Cannot write signalroutes" <<endl;
	  return 1;
  }

  out.clear();

  for (int i=0; i<n; i++){
	  Signalroute *sr = (Signalroute *) signalroutes->GetAt(i);

	  out <<sr->GetName();

	  out <<";" <<sr->getFromName();

	  out <<";" <<sr->getToName();

	  IfList<IfSignal> *signals = sr->GetSignals();
	  int m = signals->GetCount();
	  for (int j=0; j<m; j++){
		  IfSignal *s = signals->GetAt(j);
		  out <<";" <<s->GetName();
	  }
	  out <<endl;
  }
  out.close();

  fclose(file);
  printf("\n\n");
  return 1;
}



