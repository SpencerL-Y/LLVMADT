#ifndef CFAEdge_hpp
#define CFAEdge_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <unistd.h>

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
    
public:
    CFAEdge(/* args */);
    ~CFAEdge();
    CFAState* getFromState();
    CFAState* getToState();
    void setFromState(CFAState* fromState);
    void setToState(CFAState* toState);
    void mkGuard();
    Guard* getGuard();
    std::string getGuardStr();
    std::string toString();
};



}

#endif
