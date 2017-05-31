    // PL homework: hw1
// fsa.h

#ifndef _PL_HOMEWORK_FSA_H_
#define _PL_HOMEWORK_FSA_H_

#include <vector>
#include <string>
#include <map>
#include <set>
// Valid characters are alphanumeric and underscore (A-Z,a-z,0-9,_).
// Epsilon moves in NFA are represented by empty strings.

struct FSATableElement {
  int state;
  int next_state;
  std::string str;
};
typedef std::set<int> State;
typedef std::pair<State, char> StateInput;
typedef std::set <char> Inputs;
typedef std::map <StateInput, State> Ne_state;


struct FiniteStateAutomaton {
  // Make your own FSA struct here.
    Inputs inputs;
    State accept;
    Ne_state ne_state;
    State firstState;
};

// Run FSA and return true if str is matched by fsa, and false otherwise.
bool RunFSA(const FiniteStateAutomaton& fsa, const std::string& str);

bool BuildFSA(const std::vector<FSATableElement>& elements,
              const std::vector<int>& accept_states,
              FiniteStateAutomaton* fsa);

#endif //_PL_HOMEWORK_FSA_H_

