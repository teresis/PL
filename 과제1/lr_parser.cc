// PL homework: hw2
// lr_parser.cc

#include <assert.h>

#include <iostream>
#include <vector>

#include "lr_parser.h"

#define DISABLE_LOG false
#define LOG \
    if (DISABLE_LOG) {} else std::cerr

using namespace std;

bool BuildLRParser(const std::vector<LRTableElement>& elements,
                   const std::vector<LRRule>& rules,
                   LRParser* lr_parser)
{
    int i;
    int num_elements= elements.size();
    int num_rules = rules.size();
    // add elements to map
    for( i=0; i<num_elements; i++ )
    {
        lr_parser->ParseTable[ elements[i].state ][ elements[i].symbol ] = elements[i];
    }
    
    for( i=0; i<num_rules; i++ )
    {
        lr_parser->Rules[ rules[i].id ] = rules[i];
    }
  return true;
}

bool RunLRParser(const LRParser& lr_parser, const std::string& str) {
    //Phase 1 : initialize stack & input string's index
    vector<int> stack;
    int str_index = 0;
    int stack_index = 0;
    
    int reducedFactor;
    bool isReduced = false;
    
    stack.push_back(0);
    
    
    
    //Phase 2 : loop until accept comes or unexcepted input comes
    while( true )
    {
        int nextInput = str[str_index];
        
        // handle 'GOTO' after 'REDUCE'
        if( isReduced )
        {
            isReduced = false;
            nextInput = reducedFactor;
        }
        
        std::map< int, LRTableElement >::const_iterator it = lr_parser.ParseTable.find( stack[stack_index] )->second.find( nextInput );
        
        
        if( it != lr_parser.ParseTable.find( stack[stack_index] )->second.end() ) //acceptable
        {
            int ruleNum, numToPop;
            if( it->second.action==SHIFT )
            {
                    stack.push_back( nextInput );
                    stack.push_back( it->second.next_state );
                    
                    stack_index += 2;
                    str_index++;
                    break;
            }else if( it->second.action==REDUCE )
            {
                    ruleNum = it->second.next_state;
                    numToPop = lr_parser.Rules.find(ruleNum)->second.num_rhs;
                    
                    for( int i=0; i<numToPop*2; i++ )
                    {
                        stack.pop_back();
                    }
                    
                    stack_index -= numToPop*2;
                    
                    reducedFactor = lr_parser.Rules.find(ruleNum)->second.lhs_symbol;
                    isReduced = true;
                    break;
            }else if( it->second.action==GOTO )
            {
                    stack.push_back( nextInput );
                    stack.push_back( it->second.next_state );
                    
                    stack_index += 2;
                    break;
            }else if( it->second.action==ACCEPT )
                          {
                    return true;
            }       
            else
            {
                    return false;
            }
        }
        else // not acceptable
        {
            return false;
        }
    }

  return false;
}

