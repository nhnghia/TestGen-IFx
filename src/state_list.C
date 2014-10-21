/* 

 state_list.C : a List of data.

 Last modification by Mounir LALLALI mlallali@gmail.com
 19/06/2008

 Main file: mainExplorator.C
 */

#include "state_list.h"
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include "simulator.h"
#include <vector>

StateList::StateList() {
	pos_current = 0;
	LocalDepth = 0;
}

StateList::~StateList() {
	_state.clear();
}

void StateList::clear() {
	_state.clear();
}

void StateList::put(StateNode p) {
	list<StateNode>::iterator i = _state.end();
	_state.insert(i, p);
}

void StateList::put(IfConfig* s, long int depth, long int father, IfLabel *label) {

	StateNode p;
	p.state = s;
	p.pos = pos_current;
	p.depth = depth + 1;
	p.father = father;

	if (label != NULL){
		p.label = label->copy();
	}


	list<StateNode>::iterator i = _state.end();
	_state.insert(i, p);
	pos_current++;
	return;
}

void StateList::remove_state(IfConfig *s) {
	list<StateNode>::iterator i;
	for (i = _state.begin(); i != _state.end(); i++)
		if (s == (*i).state) {
			_state.erase(i);
			return;
		}
}

IfConfig* StateList::get() {
	list<StateNode>::iterator i = _state.begin();
	return (*i).state;
}

bool StateList::isEmpty() {
	return _state.empty();
}

long int StateList::getPos(IfConfig* s) {
	list<StateNode>::iterator i;
	for (i = _state.begin(); i != _state.end(); i++)
		if (s == (*i).state) {
			return (*i).pos;
		}
	return -1;
}

long int StateList::getFirstPos() {
	list<StateNode>::iterator i;
	i = _state.begin();
	return (*i).pos;
}

long int StateList::getLastPos() {
	list<StateNode>::iterator i;
	i = _state.end();
	i--;
	return (*i).pos;
}

long int StateList::getDepth(IfConfig* s) {
	list<StateNode>::iterator i;
	for (i = _state.begin(); i != _state.end(); i++)
		if (s == (*i).state) {
			return (*i).depth;
		}
	return -1;
}

void StateList::setDepth(IfConfig* s, long int depth) {
	list<StateNode>::iterator i;
	for (i = _state.begin(); i != _state.end(); i++)
		if (s == (*i).state) {
			(*i).depth = depth;
		}
}

long int StateList::getFatherId(IfConfig* s) {
	list<StateNode>::iterator i;
	for (i = _state.begin(); i != _state.end(); i++)
		if (s == (*i).state) {
			return (*i).father;
		}
	return -1;
}

bool StateList::getFather(IfConfig* s, StateNode& p) {
	StateNode node;
	list<StateNode>::iterator i;
	for (i = _state.begin(); i != _state.end(); i++)
		if (s == (*i).state) {
			node = *i;
			if (node.pos == 0) {
				p = node;
				return true;
			}
		}
	for (i = _state.begin(); i != _state.end(); i++) {
		if (node.father == (*i).pos) {
			p = *i;
			return true;
		}
	}
	return false;
}

bool StateList::getFather(StateNode n, StateNode& p) {
	list<StateNode>::iterator i;
	if (n.father == -1) {
		p = n;
		return true;
	}
	for (i = _state.begin(); i != _state.end(); i++) {
		if (n.father == (*i).pos) {
			p = *i;
			return true;
		}
	}
	return false;
}

void StateList::getNode(IfConfig* s, StateNode& p) {
	list<StateNode>::iterator i;
	for (i = _state.begin(); i != _state.end(); i++)
		if (s == (*i).state) {
			p = (*i);
			return;
		}
}

void StateList::printPath(IfConfig* s) {
	StateNode node;
	bool found;
	do {
		found = getFather(s, node);
		if (found) {
			s = node.state;
		}
	} while ((node.father != -1) && (found));
}

vector<IfLabel *> StateList::getPath(StateNode state_node) {
	StateNode nod, node;
	bool found;
	vector<IfLabel *> lst;
	int maxDepth = 0;

	if (state_node.father == -1){
		return lst;
	}else {
		nod = state_node;

		do {
			found = getFather(nod, node);
			if (found) {
				//print_aldebaran_suite(n.father, n.label_id, n.pos);
				if (nod.label != NULL)
					lst.insert(lst.begin(), nod.label);
				//testCase.insert(testCase.end(), n.testCase.begin(), n.testCase.end());
				nod = node;
			}
		} while ((node.father != -1) && (found));
	}
	return lst;
}

long int StateList::getSize() {
	return _state.size();
}

StateNode StateList::getNode(long int pos, long int init) {
	list<StateNode>::iterator i = _state.end();
	for (long int j = 1; j < init; j++)
		i++;
	while (i != _state.begin()) {
		if (pos == (*i).pos)
			return *i;
		i--;
	}
	return *i;
}

void StateList::update(StateNode p) {
	list<StateNode>::iterator i = _state.begin();
	for (long int j = 1; j <= p.pos; j++)
		i++;
	if ((*i).state == p.state)
		(*i).father = -1;
}
