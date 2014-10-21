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

/**
 * Sum up the consecutive Delays
 */
TestCase TestCase::optimize(){
	TestCase lst;
	int n = size();
	int i=0;

	while (i<n){
		Event *ev = at(i++);

		//ev is Delay
		if (dynamic_cast<Delay*>(ev) != NULL){
			Delay *delay = dynamic_cast<Delay*>(ev);

			while (i<n){
			//find the next delay
				if (dynamic_cast<Delay*>(at(i)) != NULL){
					delay->delay += dynamic_cast<Delay*>(at(i))->delay;
					i++;
				}else
					break;
			}

			if (i<n)
				lst.push_back(delay);
		}else{
			lst.push_back(ev);
		}
	}

	//!;	{OBU}0;	 MARequest{10};	{RBC}0
	//?;	env;	 DLocation{10};	{RBC}0
	//delay 2
	//?;	env;	 MARequest{10};	{RBC}0
	//==> change the last "env" to "{OBU}0
	n = lst.size();
	for (int i=0; i<n; i++){
		Event *ev = lst.at(i);
		if (dynamic_cast<Input*>(ev) != NULL){
			Input *input = (Input *) ev;
			if (input->sender.compare("env") == 0){
				for (int j=0; j<i; j++){
					ev = lst.at(j);
					if (dynamic_cast<Output *>(ev) != NULL){
						Output *output = (Output *) ev;
						if (output->label.compare(input->label) == 0 && output->receiver.compare(input->receiver) == 0){
							input->sender = output->sender;
						}
					}
				}
			}
		}
	}

	return lst;

}

void TestCase::print(std::ostream& os){
	int n = size();
	for (int i=0; i<n; i++)
		os << at(i)->toString() <<endl;
}


int TestCase::add(IfLabel *label){
	if (label == NULL)
		return 0;

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

TestCase TestCase::concat(TestCase t){
	TestCase tc;
	tc.reserve(size() + t.size());
	int n = size();
	for (int i=0; i<n; i++)
		tc.push_back(at(i));

	n = t.size();
	for (int i=0; i<n; i++)
		tc.push_back(t.at(i));

	return tc;
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

				// ? -- -->partner
				if (dynamic_cast<Input *> (ev) != NULL){
					if (sender.compare("env") == 0)
						localTestCase.push_back(new Output("t", label, receiver));
					else if (partner.compare(receiver) == 0)
						localTestCase.push_back(ite->copy());
				}
				// ! partner --> env
				else if (dynamic_cast<Output *> (ev) != NULL){
					if (receiver.compare("env") == 0)
						localTestCase.push_back(new Input(sender, label, "t"));
					else if (partner.compare(sender) == 0)
						localTestCase.push_back(ite->copy());
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
