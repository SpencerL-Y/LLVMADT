#ifndef DFAState_hpp
#define DFAState_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../abstract/State.hpp"
namespace llvmadt
{
template <class A>
class DFAState : public State<A>
{
private:

public:
    DFAState(/* args */);
    ~DFAState();
};
    
} // namespace llvmadt


#endif
