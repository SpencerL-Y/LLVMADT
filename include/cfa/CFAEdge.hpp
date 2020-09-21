#ifndef CFAEdge_hpp
#define CFAEdge_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>

#include "Guard.hpp"
#include "CFAState.hpp"

class CFAState;
class CFAEdge
{
private:
    /* data */
    CFAState* fromState;
    CFAState* toState;
    Guard guard;
    
public:
    CFAEdge(/* args */);
    ~CFAEdge();
    CFAState* getFromState();
    CFAState* getToState();
    std::string getGuardStr();
    std::string toString();
};


CFAEdge::CFAEdge(/* args */)
{
}

CFAEdge::~CFAEdge()
{
}


#endif
