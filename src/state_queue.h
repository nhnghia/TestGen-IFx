/* 

state_queue.h : a queue of data.

Last modification: 
02/02/2009

Main file: mainExplorator.C
*/

#ifndef __STATE_QUEUE_HH__
#define __STATE_QUEUE_HH__

#include <iostream>
#include <map>
#include <queue>
#include <list>
#include "simulator.h"

using namespace std;

struct stateQNode {
  IfConfig* state;
  long int pos;
  long int depth;
  long int father;
} ;


class StateQueue{
 public:
  StateQueue();
  ~StateQueue();
  long int put (IfConfig *s,long int depth,long int father);
  void put(stateQNode s);
  stateQNode get();
  stateQNode getNode(int pos);
  bool isEmpty();
  int getSize();
  void clear();
  
 protected:
 private:
  queue<stateQNode , list<stateQNode> > _state;
  long int pos_current; //current position
};

#endif	// __STATE_QUEUE_HH__
