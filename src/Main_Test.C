/*
 * Main_Test.C
 *
 *  Created on: 29 juin 2014
 *      Author: nhnghia
 */

#include <stdio.h>
#include <stdlib.h>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include "Tool.h"

using namespace std;
int main(int argc, char * argv[]) {
	string s = "Bonjour tous le  monde  ";
	vector<string> el = tsp::Tool::split(s, ' ');
	for (string procname : el){
					cout <<" ---" <<procname<<"---" << endl;
	}

}
