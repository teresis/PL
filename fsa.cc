// PL homework: hw1
// fsa.cc

#include <iostream>

#include "fsa.h"

#define DISABLE_LOG true
#define LOG \
    if (DISABLE_LOG) {} else std::cerr

using namespace std;
const string eps = "";
bool RunFSA(const FiniteStateAutomaton& fsa, const string& str) {
  // Implement this function.
    State currentState = fsa.firstState;
    int strLength = str.length()    ;
    
    for(int iStr=0; iStr<strLength; iStr++)
    {
        char inputChar = str[iStr];
        StateInput newInput(currentState, inputChar);
        
        //find the state matched with current state and input char
        Ne_state::const_iterator foundState = fsa.ne_state.find(newInput);
        if( foundState != fsa.ne_state.end() )
        {
            currentState = fsa.ne_state.at(newInput);
        }
        //if input not found, return false
        else
        {
            return false;
        }
    }
    
    //iterates fsa->acceptable set, if any found, return true.
    for(State::iterator iterator=fsa.accept.begin(); iterator!=fsa.accept.end(); iterator++)
    {
        for(State::iterator stateIterator=currentState.begin(); stateIterator!=currentState.end(); stateIterator++)
        {
            if(*stateIterator == *iterator)
                return true;
            
            //for faster search : std::set is already sorted.
            else if(*stateIterator > *iterator)
                break;
        }
    }
    
    
    
    return false;
}

void handleEpsilonMoves(const std::vector<FSATableElement>& elements, int num_elements,
                        State* state, int startNum)
{
    int iElem = startNum;
    int currState = elements[iElem].state;
    
    //finds all Epsilon-Moves, and add onto one state.
    while(elements[iElem].state == currState &&
          elements[iElem].str == eps)
    {
        if( state->find(elements[iElem].next_state) != state->end() )
        {
            iElem++;
            if(iElem == num_elements)
                break;
            continue;
        }
        
        state->insert(elements[iElem].next_state);
        
        int jElem;
        for(jElem=0; jElem<num_elements; jElem++)
        {
            if(elements[jElem].state == elements[iElem].next_state)
                break;
        }
        //if Epsilon-Moved state can Epsilon-Move again, call this function again and add on.
        if(elements[jElem].str == eps)
        {
            handleEpsilonMoves(elements, num_elements, state, jElem);
        }
        
        //to next TableElement
        iElem++;
        if(iElem == num_elements)
            break;
    }
}
void getNextState(const std::vector<FSATableElement>& elements, int num_elements,
                  FiniteStateAutomaton* fsa, State currState)
{
    State nextState;
    
    for(Inputs::iterator iInput=fsa->inputs.begin(); iInput!=fsa->inputs.end(); iInput++)
    {
        char inputCh = *iInput;
        nextState.clear();
        
        //iterate through currentState's element
        for(State::iterator iter=currState.begin(); iter!=currState.end(); iter++)
        {
            //iterate through elements, if state found, get output of 'inputCh' move.
            for(int iElem=0; iElem<num_elements; iElem++)
            {
                for(int i=0;i<elements[iElem].str.length();i++)
                {
                    if(elements[iElem].state == *iter && elements[iElem].str.at(i) == inputCh)
                    {
                        //add next state number to nextState
                        nextState.insert(elements[iElem].next_state);
                        int jElem;
                        //checking epsilon-move
                        for(jElem=0; jElem<num_elements; jElem++)
                        {
                        if(elements[jElem].state == elements[iElem].next_state)
                            break;
                        }
                        handleEpsilonMoves(elements, num_elements, &nextState, jElem);
                    }
                }
            }
        }
        
        StateInput newSwI(currState,inputCh);
        
        //if LOOPs or next state is empty, continue looping.
        if(fsa->ne_state.find(newSwI) != fsa->ne_state.end() ||
           nextState.empty())
        {
            continue;
        }
        else
        {
            fsa->ne_state[newSwI] = nextState;
            getNextState(elements, num_elements, fsa, nextState);
        }
    }
}

bool BuildFSA(const std::vector<FSATableElement>& elements,
              const std::vector<int>& accept_states,
              FiniteStateAutomaton* fsa) {
  // Implement this function.
    int num_element=elements.size();
  for(int iAccept=0; iAccept<accept_states.size(); iAccept++)
  {
      fsa->accept.insert(accept_states[iAccept]);
                 }
   for(int iElem=0; iElem<num_element; iElem++){
         for(int i= 0;i<elements[iElem].str.length();i++)
         {
             fsa->inputs.insert(elements[iElem].str.at(i));
         }
   }
   State firstState;
     firstState.insert(elements[0].state);
    handleEpsilonMoves(elements, num_element, &firstState, 0);
    fsa->firstState = firstState;
    
    //get states' moves.
    getNextState(elements, num_element, fsa, firstState);

    

  LOG << "num_elements: " << elements.size()
      << ", accept_states: " << accept_states.size() << endl;
  return true;
}

