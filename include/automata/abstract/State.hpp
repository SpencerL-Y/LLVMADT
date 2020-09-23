#ifndef State_hpp
#define State_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./Transition.hpp"
#include "../alphabet/Alphabet.hpp"


namespace llvmadt{
template<class A>
class State
{
protected:
    int id;
    std::list<Transition<A>*> stateTransitions;
public:
    void addTransition(Transition<A>* tran);
    void delTransition(int from, Letter<A>* l, int to);
    void getId();
    void setId(int id);
    State(/* args */);
    ~State();
};

}

#endif