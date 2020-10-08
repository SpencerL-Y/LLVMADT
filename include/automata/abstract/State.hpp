#ifndef State_hpp
#define State_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <set>
#include "./Transition.hpp"
#include "../alphabet/Alphabet.hpp"


namespace llvmadt{

class State
{
protected:
    int id;
    std::set<Transition*> stateTransitions;
    bool isAccept;
    bool isInit;
    Alphabet* alphabet;
public:
    virtual void addTransition(Transition* tran)=0;
    virtual void delTransition(int from, Letter* l, int to)=0;
    virtual void delTransition(Transition* tran)=0;
    virtual std::string toString()=0;
    std::set<Transition*>& getStateTransitions();
    int getId();
    void setId(int id);
    bool isAccState();
    void setAcc();
    bool isInitialState();
    void setInit(); 
    bool hasTransition(int from, Letter* l, int to);
    Alphabet* getAlphabet();
    void setAlphabet(Alphabet* alpha);
    State(/* args */);
    State(Alphabet* alpha);
    ~State();
};

}

#endif
