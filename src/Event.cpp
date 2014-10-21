/*
 * Event.cpp
 *
 *  Created on: 30 juin 2014
 *      Author: nhnghia
 */

#include "Event.h"
#include "Tool.h"
#include <typeinfo>
#include <regex>
#include <string>

namespace tsp {

Event::Event(std::string l) {
	label = l;
}

Event::~Event() {
}

/**
 * parser an IfEvent to an Input, Output, or Delay
 */
Event* Event::parser(IfEvent *ev){

	//contain signals in an IF file
	static vector<Interaction *> SIGNALS;
	static bool readSignalroute = false;
	if (readSignalroute == false){
		readSignalroute = true;
		//file name is the same with the one in getSignalRoute.C
		char *filename = "/tmp/if-signalroute.XXXXXX";
		ifstream in(filename);

		if (!in.fail()){
			string line;
			cout <<line <<endl;
			while (getline(in, line)){
				vector<string> str = tsp::Tool::split(line, ';');
				int n = str.size();
				if (n >= 4){
					string sender = str[1];
					string receiver = str[2];
					for (int i=3; i<n; i++){
						SIGNALS.push_back(new Interaction(sender, str[i], receiver));
					}
				}
			}
			//remove(filename);
		}
	}

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
		if (partner.empty())
			partner = "env";

		//IF simulator always put partner := pid for any IfEvent::INPUT
		//However we need to distinguish that an IfEvent::INPUT comes from ENV or from another IfProcess

		if (partner.compare(pid) == 0){
			partner = "env";
			int n = SIGNALS.size();
			for (int i=0; i<n; i++){
				Interaction *ite = SIGNALS.at(i);
				if (label.find(ite->label) != string::npos){

					if (pid.find(ite->sender) != string::npos){
						partner = ite->receiver;
						break;
					}else if (pid.find(ite->receiver) != string::npos){
						partner = ite->sender;
						break;
					}
				}
			}
		}

		//label = p1={distance=1, speed=2},p2=3
		//remove p1=, p2= .. from label
		std::regex exp ("p(\\d+)=");
		label = std::regex_replace(label, exp, "");

		//label = {distance=1, speed=2},3
		//remove distance=, speed=, ..
		std::regex exp2("(\\w+)=");
		label = std::regex_replace(label, exp2, "");
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

Event * Event::copy(){
	return new Event(label);
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

Event * Input::copy(){
	return new Input(sender, label, receiver);
}

string Input::toString() {
	string s = Interaction::toString();
	return string("?;\t") + s;
}

Output::Output(string sender, string label, string receiver): Interaction(sender, label, receiver)  {
}

Event * Output::copy(){
	return new Output(sender, label, receiver);
}

std::string Output::toString() {
	string s = Interaction::toString();
	return string("!;\t") + s ;
}

Delay::Delay(int d) : Event("delay"){
	delay = d;
}

Event * Delay::copy(){
	return new Delay(delay);
}

std::string Delay::toString() {
	string s = Event::toString();
	return s + string(" ") + to_string(delay);
}
} /* namespace tsp */
