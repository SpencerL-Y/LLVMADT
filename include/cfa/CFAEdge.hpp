#ifndef CFAEdge_hpp
#define CFAEdge_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>
#include "z3++.h"

#include "./Guard.hpp"

namespace llvmadt{
class CFAState;
class CFAEdge
{
private:
    /* data */
    CFAState* fromState;
    CFAState* toState;
    Guard* guard;
    z3::context* c;
    
    
public:
    CFAEdge(/* args */);
    ~CFAEdge();
    CFAState* getFromState();
    CFAState* getToState();
    void setFromState(CFAState* fromState);
    void setToState(CFAState* toState);
    void mkGuard(z3::expr* expr);
    Guard* getGuard();
    std::string getGuardStr();
    std::string toString();
    z3::context* getContext();
    void setContext(z3::context* c);
};



}

#endif
