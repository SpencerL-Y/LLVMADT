#ifndef State_hpp
#define State_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./Transition.hpp"
#include "./Letter.hpp"


namespace llvmadt{
class State
{
protected:
    int id;
    std::list<Transition*> stateTransitions;
public:
    void addTransition(Transition* tran);
    void delTransition(int from, Letter* l, int to);
    void getId();
    void setId(int id);
    State(/* args */);
    ~State();
};

}

#endif