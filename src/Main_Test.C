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
//#include "Tool.h"

using namespace std;

class Test{
public:
	static void init(){
		 bool b = false;
		if (b)
			return;
		b = true;
		cout <<"OK";
	}
};

int main(int argc, char * argv[]) {
	string s = "Bonjour tous le  monde  ";

	Test::init();
	Test::init();
	Test::init();
}
