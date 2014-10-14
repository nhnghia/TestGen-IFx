/*
 * TestCase.cpp
 *
 *  Created on: 29 juin 2014
 *      Author: nhnghia
 */

#include "TestCase.h"

namespace tsp {
TestCase::TestCase(){
}
TestCase::~TestCase(){
}

void TestCase::optimize(){

	for (int i=0; i<size(); i++){
		Event *ev = at(i);
		//ev is Delay
		if (dynamic_cast<Delay*>(ev) != NULL){
			Delay *delay = dynamic_cast<Delay*>(ev);

			//find the next delay
			if (i<size() - 1)
				if (dynamic_cast<Delay*>(at(i+1)) != NULL){
					delay->delay += dynamic_cast<Delay*>(at(i+1))->delay;
					//remove
					erase(begin()+i+1);
			}
		}
	}

	//the last event is  Delay
	if (size() > 0)
		if (dynamic_cast<Delay*>(at(size() - 1)) != NULL){
			//erase(end());
			erase(begin() + size() - 1);
		}
}

void TestCase::print(std::ostream& os){
	int n = size();
	for (int i=0; i<n; i++)
		os << at(i)->toString() <<endl;
}


int TestCase::add(IfLabel *label){
	int n=label->getLength();
	int d=0;
	for (int i=0; i<n; i++){
		Event *ev = Event::parser(label->getAt(i));
		if (ev != NULL){
			d++;
			TestCase::push_back(ev);
		}
	}
	return d;
}

set<string> TestCase::getPartners(){
	int n = size();
	//get list of partners
	set<string> partners;
	for (int i=0; i<n; i++){
		Event *ev = at(i);
		//ev is not Delay (ev is either a sending or a reception
		if (dynamic_cast<Delay*>(ev) == NULL){
			Interaction *ite = dynamic_cast<Interaction*>(ev);
			partners.insert(ite->sender);
			partners.insert(ite->receiver);
		}
	}
	//remove "env"
	partners.erase("env");
	return partners;
}

TestCase TestCase::project(string partner) {
	TestCase localTestCase;
	int n = size();
	for (int i=0; i<n; i++){
		Event *ev = at(i);
		if (dynamic_cast<Delay*>(ev) != NULL){
			Delay *d = new Delay(dynamic_cast<Delay*>(ev)->delay);
			localTestCase.push_back(d);
		}else{
			Interaction *ite = dynamic_cast<Interaction*>(ev);
			string sender = ite->sender;
			string receiver = ite->receiver;
			string label = ite->label;

			//consider only event related to the partner
			if (partner.compare(sender) == 0 || partner.compare(receiver) == 0){

				//an observation
				if (sender.compare("env") != 0 && receiver.compare("env") != 0){
					localTestCase.push_back(ev->copy());
				}
				// ? env-->partner
				else if (dynamic_cast<Input *> (ev) != NULL && sender.compare("env") == 0){
					localTestCase.push_back(new Output("t", label, receiver));
				}
				// ! partner --> env
				else if (dynamic_cast<Output *> (ev) != NULL && receiver.compare("env") == 0){
					localTestCase.push_back(new Input(sender, label, "t"));
				}

			}
		}
	}

	return localTestCase;
}


void TestCase::printMsc(ostream& out) {
	out <<"#MSC for test case" <<endl;
	out <<"msc{" <<endl;
	out <<"  t, impl, obs;" <<endl;
	int n = size();
	for (int i=0; i<n; i++){
		//Event *e = at(i);
		//out << "  ";
		//if (e )<<at(i)->toString() <<endl;
	}

	out <<"}" <<endl;
}
} /* namespace tsp */
