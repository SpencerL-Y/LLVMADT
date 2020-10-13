#ifndef CFA_hpp
#define CFA_hpp
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <set>
#include <unistd.h>
#include "./CFAState.hpp"
#include "./CFAEdge.hpp"
#include "z3++.h"
namespace llvmadt{
// CFA is an intermediate automata data structure used for storing the information of IR CFGs

class CFA
{
private:
    // a state is a valuation of variables
    // startstate : indexed with 0
    std::set<CFAState*> states; 
    // edge can be regarded as change of valuation
    std::set<CFAEdge*> edges;
    std::set<std::string> VarNames;
    int stateNum;
    std::string name;
    z3::context* c;
    
public:
    CFA(/* args */);
    ~CFA();
    std::set<CFAState*>& getStates();
    void setStates(std::set<CFAState*>& states);
    int getStateNum();
    void addState(int id);
    void addState(CFAState* state);
    CFAState* getState(int id);
    void addEdge(int fromId, int toId);
    void addEdge(CFAState* fromState, z3::expr* guard_expr, CFAState* toState);
    void addEdge(int fromId, z3::expr* guard_expr, int toId);
    CFAEdge* getEdge(int fromId, int toId);
    std::set<CFAEdge*>& getEdges();
    void setName(std::string name);
    std::string getName();
    std::string toString();
    bool hasStateId(int id);
    bool hasEdgeId(int fromId, int toId);
    z3::context* getContext();
    void setContext(z3::context* c);

    void setVarNames(std::set<std::string>& varNames);
    std::set<std::string> getVarNames();
};


}


#endif
