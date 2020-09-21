#ifndef CFA_hpp
#define CFA_hpp
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <unistd.h>
#include "./CFAState.hpp"

class CFA
{
private:
    std::list<CFAState> states;
    
public:
    CFA(/* args */);
    ~CFA();
    std::list<CFAState*> getStates();
    void setStates(std::list<CFAState>& states);
    int getStateNum();
    void addState(int id);
    void addState(CFAState& state);
    CFAState* getState(int id);
    void setName(std::string name);
    std::string getName();
    std::string toString();
};

CFA::CFA(/* args */)
{
}

CFA::~CFA()
{
}


#endif
