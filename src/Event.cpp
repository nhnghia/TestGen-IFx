/*
 * Event.cpp
 *
 *  Created on: 30 juin 2014
 *      Author: nhnghia
 */

#include "Event.h"
#include "Tool.h"
namespace tsp {

Event::Event(std::string l) {
	label = l;
}

Event::~Event() {
}

/**
 * parser an IfEvent to get Input/Output
 */
Event* Event::parser(IfEvent *ev){
	if (ev->getKind() == IfEvent::INPUT){
		string sender = std::to_string(ev->getPid());
		string receiver = std::to_string(ev->getPartner());
		string label = string(ev->getValue());
		return new Input(sender, label, receiver);
	}else if (ev->getKind() == IfEvent::OUTPUT){
		string sender = std::to_string(ev->getPid());
		string receiver = std::to_string(ev->getPartner());
		string label = string(ev->getValue());
		return new Output(sender, label, receiver);
	}
	return NULL;
}
std::string Event::toString(){
	return label;
}

Interaction::Interaction(string s, string l, string r) : Event (l){
	sender = s;
	receiver = r;
}

string Interaction::toString(){
	string s = sender + ",\t " + label + ", \t" + receiver;
	return s;
}

Input::Input(std::string sender, std::string label, std::string receiver): Interaction(sender, label, receiver)  {
}

string Input::toString() {
	string s = Interaction::toString();
	return string("?") + s;
}

Output::Output(string sender, string label, string receiver): Interaction(sender, label, receiver)  {
}

std::string Output::toString() {
	string s = Interaction::toString();
	return string("!") + s ;
}

Delay::Delay(int d) : Event("delay"){
	delay = d;
}

std::string Delay::toString() {
	string s = Event::toString();
	return s + string(" ") + to_string(delay);
}
} /* namespace tsp */
