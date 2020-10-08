#ifndef Transition_hpp
#define Transition_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../alphabet/Alphabet.hpp"

namespace llvmadt{
class State;

class Transition
{
protected:
    State* fromState;
    Letter* letter;
    State* toState;
    Alphabet* alphabet;
public:
    Transition(Alphabet* alphabet);
    Transition(State* from, Letter* l, State* to);
    //Transition(State* from, Letter* l, State* to, Alphabet* alpha);
    Transition(/* args */);
    ~Transition();

    Alphabet* getAlphabet();
    void setAlphabet(Alphabet* alphabet);
    State* getFromState();
    State* getToState();
    Letter* getLetter();

};

}
#endif
