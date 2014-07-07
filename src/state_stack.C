/* 

 state_stack.C : a Stack of data.

 last update 02/02/2009 by Mounir Lallali mlallli@gmail.com

 Main file: mainExplorator.C
 */

#include "state_stack.h"

StateStack::StateStack() {
	pos_current = 0; //current position starts with the initial one
}

StateStack::~StateStack() {
}

void StateStack::put(StateNode s) {
	_state.push(s);
}

long int StateStack::put(IfConfig *s, long int depth, long int father) {
	StateNode p;
	p.state = s;
	p.pos = pos_current;
	p.depth = depth + 1;
	p.father = father;
	_state.push(p);
	pos_current++;
	return p.pos;
}

StateNode StateStack::get() {
	StateNode q = _state.top();
	_state.pop();
	return q;
}

bool StateStack::isEmpty() {
	return _state.empty();
}

void StateStack::remove_state() {
	_state.pop();
}

void StateStack::clear() {
	while (!isEmpty())
		_state.pop();
}
