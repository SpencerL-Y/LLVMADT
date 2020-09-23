#ifndef Transition_hpp
#define Transition_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../alphabet/Alphabet.hpp"

namespace llvmadt{
template <class A> class State;
template <class A>
class Transition
{
protected:
    State<A>* fromState;
    Letter<A>* letter;
    State<A>* toState;
public:
    Transition(/* args */);
    ~Transition();
};

}
#endif
