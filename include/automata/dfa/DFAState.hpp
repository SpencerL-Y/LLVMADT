#ifndef DFAState_hpp
#define DFAState_hpp
#include <iostream>
#include <stdlib.h>
#include "../abstract/State.hpp"
namespace llvmadt
{

class DFAState : public State
{
private:

public:
    DFAState(/* args */);
    ~DFAState();
};
    
} // namespace llvmadt


#endif