#ifndef CFA_hpp
#define CFA_hpp
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <unistd.h>
#include "./CFAState.hpp"
#include "./CFAEdge.hpp"
#include "z3++.h"
namespace llvmadt{
class CFA
{
private:
    std::list<CFAState*> states; 
    std::list<CFAEdge*> edges;
    int stateNum;
    std::string name;
    z3::context* c;
    
public:
    CFA(/* args */);
    ~CFA();
    std::list<CFAState*> getStates();
    void setStates(std::list<CFAState*>& states);
    int getStateNum();
    void addState(int id);
    void addState(CFAState* state);
    CFAState* getState(int id);
    void addEdge(int fromId, int toId);
    void addEdge(CFAState* fromState, z3::expr guard_expr, CFAState* toState);
    void addEdge(int fromId, z3::expr guard_expr, int toId);
    CFAEdge* getEdge(int fromId, int toId);
    std::list<CFAEdge*>& getEdges();
    void setName(std::string name);
    std::string getName();
    std::string toString();
    bool hasStateId(int id);
    bool hasEdgeId(int fromId, int toId);
    z3::context* getContext();
    void setContext(z3::context* c);
};


}


#endif
