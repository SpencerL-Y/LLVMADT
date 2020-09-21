#ifndef CFA_hpp
#define CFA_hpp
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <unistd.h>
#include "./CFAState.hpp"
#include "./CFAEdge.hpp"
class CFAState;
class CFAEdge;
class CFA
{
private:
    std::list<CFAState*> states; 
    std::list<CFAEdge*> edges;
    int stateNum;
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
    void addEdge(CFAState* fromState, CFAState* toState);
    CFAEdge* getEdge(int fromId, int toId);
    std::list<CFAEdge*>& getEdges();
    void setName(std::string name);
    std::string getName();
    std::string toString();
};

CFA::CFA(/* args */)
{
}

CFA::~CFA()
{
    for(CFAEdge* edge : this->edges){
        delete(edge);
    }
    for(CFAState* state : this->states){
        delete(state);
    }
}


#endif
