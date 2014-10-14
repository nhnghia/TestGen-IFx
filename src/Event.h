/*
 * Event.h
 *
 *  Created on: 30 juin 2014
 *      Author: nhnghia
 *
 *  Basic events: input, output, delay
 */

#ifndef EVENT_H_
#define EVENT_H_
#include <string>
#include <stdlib.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <stdio.h>
#include "simulator.h"
#include "Tool.h"

using namespace xercesc;
using namespace std;

namespace tsp {
using namespace std;
class Event{
public :
	string label;
	Event(string label);
	virtual ~Event();
	virtual string toString();

	/**
	 * convert IfEvent (input or output) to Event (Input or Output)
	 */
	static Event* parser(IfEvent *l);

	virtual Event *copy();
private:
};




class Interaction : public Event{
public:
	string sender, receiver;
	Interaction(string sender, string label, string receiver);
	virtual string toString();
private:

};
class Input : public Interaction{
public:
	Input(string sender, string label, string receiver);
	virtual string toString();
	Event *copy();
};

class Output : public Interaction{
public:
	Output(string sender, string label, string receiver);
	virtual string toString();
	Event *copy();
};

class Delay : public Event{
public:
	int delay;
	Delay(int d);
	virtual string toString();
	Event *copy();
};

} //end namespace


#endif /* EVENT_H_ */
