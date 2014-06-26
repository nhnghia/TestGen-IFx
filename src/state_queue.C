/* 

state_queue.C : a Queue of data.   

Main file: mainExplorator.C
*/

#include "state_queue.h"

StateQueue::StateQueue()
{
  pos_current = 0; //current position is the initial one
}

StateQueue::~StateQueue()
{
}

void StateQueue::put(stateQNode s)
{
  _state.push(s);
}

long int StateQueue::put(IfConfig *s,long int depth,long int father)
{
  stateQNode p;
  p.state = s;
  p.pos = pos_current; 
  p.depth = depth + 1;
  p.father = father;
  _state.push(p);
  pos_current++;
  return p.pos;
}

int StateQueue::getSize() 
{
  return _state.size();
}

stateQNode StateQueue::get()
{
  stateQNode  p = _state.front();
  _state.pop();
  return p;
}

stateQNode StateQueue::getNode(int pos)
{
  stateQNode p;
  int i = 1;
  while (i<=pos) {
    p = _state.front();
    _state.pop();
    i++;
  }
  return p;
}

bool StateQueue::isEmpty()
{
  return _state.empty();
}

void StateQueue::clear()
{
  while (!isEmpty())
    _state.pop();
}

