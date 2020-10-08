#ifndef DFAState_hpp
#define DFAState_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../abstract/State.hpp"
namespace llvmadt
{

class DFAState : public State
{
private:

public:

    void addTransition(Transition* tran);
    void delTransition(int from, Letter* l, int to);
    void delTransition(Transition* tran);
    DFAState* executeLetter(Letter* l);
    std::string toString();
    DFAState();
    DFAState(Alphabet* alphabet);
    ~DFAState();
};
    
} // namespace llvmadt


#endif
