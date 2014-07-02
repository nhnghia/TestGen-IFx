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
	unsigned k = ev->getKind();
	string pid, partner, label;
	if (k == IfEvent::INPUT || k == IfEvent::OUTPUT){
		label = string(ev->getValue());
		string str = ev->string();
		//e.g., str = <<{client}0 ?Input{p1=1}{client}0>>

		//remove << and >>
		str = str.substr(2, str.length()-5);
		str.erase(str.find(label), label.length());

		int d = str.find(' ');
		//not found
		pid = str.substr(0, d);
		partner = str.substr(d+1+1);	//remove space and ? or !
		if (partner.empty() || pid.compare(partner) == 0)
			partner = "env";
	}


	if (k == IfEvent::INPUT){
		return new Input(partner, label, pid);
	}else if (k == IfEvent::OUTPUT){
		return new Output(pid, label, partner);
	}else if (k == IfEvent::TICK){
		int delay = atoi(ev->getValue());
		return new Delay(delay);
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
	string s = sender + ";\t " + label + ";\t" + receiver;
	return s;
}

Input::Input(std::string sender, std::string label, std::string receiver): Interaction(sender, label, receiver)  {
}

string Input::toString() {
	string s = Interaction::toString();
	return string("?;\t") + s;
}

Output::Output(string sender, string label, string receiver): Interaction(sender, label, receiver)  {
}

std::string Output::toString() {
	string s = Interaction::toString();
	return string("!;\t") + s ;
}

Delay::Delay(int d) : Event("delay"){
	delay = d;
}

std::string Delay::toString() {
	string s = Event::toString();
	return s + string(" ") + to_string(delay);
}
} /* namespace tsp */
