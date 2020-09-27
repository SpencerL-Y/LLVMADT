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

    void addTransition(Transition<A>* tran);
    void delTransition(int from, Letter<A>* l, int to);
    DFAState<A>* executeLetter(Letter<A>* l);
    std::string toString();
    DFAState();
    DFAState(Alphabet<A>* alphabet);
    ~DFAState();
};
    
} // namespace llvmadt


#endif
