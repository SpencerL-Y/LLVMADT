#ifndef Transition_hpp
#define Transition_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../alphabet/Alphabet.hpp"

namespace llvmadt{
template <class T> class State;
template <class A>
class Transition
{
protected:
    State<A>* fromState;
    Letter<A>* letter;
    State<A>* toState;
    Alphabet<A>* alphabet;
public:
    Transition(Alphabet<A>* alphabet);
    Transition(State<A>* from, Letter<A>* l, State<A>* to);
    Transition(/* args */);
    ~Transition();

    Alphabet<A>* getAlphabet();
    void setAlphabet(Alphabet<A>* alphabet);
    State<A>* getFromState();
    State<A>* getToState();
    Letter<A>* getLetter();
    
};

}
#endif
