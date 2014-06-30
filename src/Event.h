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

#include "simulator.h"

namespace tsp {
using namespace std;
class Event{
public :
	string label;
	Event(string label);
	virtual ~Event();
	virtual string toString();

	static Event* parser(IfEvent *l);
};

class Interaction : public Event{
public:
	string sender, receiver;
	Interaction(string sender, string label, string receiver);
	virtual string toString();

};
class Input : public Interaction{
public:
	Input(string sender, string label, string receiver);
	virtual string toString();
};

class Output : public Interaction{
public:
	Output(string sender, string label, string receiver);
	virtual string toString();
};

class Delay : public Event{
public:
	int delay;
	Delay(int d);
	virtual string toString();
};

} //end namespace


#endif /* EVENT_H_ */
