/* 

 state_stack.h : a Stack of data.

 Last modification by Mounir Lallali mlallali@gmail.com
 02/02/2009

 Main file: mainExplorator.C
 */

#ifndef __STATE_STACK_HH__
#define __STATE_STACK_HH__

#include <iostream>
#include <map>
#include <list>
#include <stack>
#include "state_list.h"
#include "simulator.h"

using namespace std;

struct StateNode;
// defined in the "state_list.h" file

class StateStack {
public:
	StateStack();
	~StateStack();
	void put(StateNode s);
	long int put(IfConfig *s, long int depth, long int father);
	void remove_state();
	void clear();
	StateNode get();
	bool isEmpty();

protected:
private:
	stack<StateNode, list<StateNode> > _state;
	long int pos_current; //Current position
};

#endif	// __STATE_STACK_HH__
