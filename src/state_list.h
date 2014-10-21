/* 

state_list.h : a List of data.

Last modification by Mounir LALLALI mlallali@gmail.com
2/02/2009
   
Main file: mainExplorator.C
*/

#ifndef __STATE_LIST_HH__
#define __STATE_LIST_HH__

#include <stdlib.h>
#include <string>
#include <fstream>
#include <map>
#include <list>
#include <string.h>
#include "state_stack.h"
#include "simulator.h"
#include <vector>
#include "TestCase.h"

using namespace std;

struct StateNode {
  IfConfig* state;
  long int pos;
  long int depth;
  long int father;
  IfLabel *label;
} ;

class StateList{
 public:
  StateList();
  ~StateList();
  void clear();
  void put (IfConfig* s,long int depth, long int father, IfLabel *label);
  void put (StateNode p);
  void update (StateNode p);
  void remove_state(IfConfig* s);
  long int getPos(IfConfig* s);
  long int getFirstPos(); 
  long int getLastPos();
  long int getDepth(IfConfig* s);
  void setDepth(IfConfig* s,long int depth);
  bool getFather(IfConfig* s, StateNode& p);
  bool getFather(StateNode n, StateNode& p);
  void getNode(IfConfig* s, StateNode& p);
  StateNode getNode(long int pos,long int init);
  long int getFatherId(IfConfig* s);
  void printPath(IfConfig* s);
  vector<IfLabel *> getPath(StateNode state_node);
  void dump_list();
  long int getSize();
  IfConfig* get();
  bool isEmpty();
  
protected:
  
 private:
  list<StateNode> _state;
  long int pos_current;
  long int LocalDepth; // local depth (in a neighborhood)
};

#endif	// __STATE_LIST_HH__
