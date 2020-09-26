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
    bool isAccept;
    bool isInit;
    Alphabet<A>* alphabet;
public:
    void addTransition(Transition<A>* tran)=0;
    void delTransition(int from, Letter<A>* l, int to)=0;
    int getId();
    void setId(int id);
    bool isAccState();
    void setAcc();
    bool isInitialState();
    void setInit(); 
    Alphabet<A>* getAlphabet();
    void setAlphabet(Alphabet<A>* alpha);
    State(/* args */);
    State(Alphabet<A>* alpha);
    ~State();
};

}

#endif