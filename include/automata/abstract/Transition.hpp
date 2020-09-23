#ifndef Transition_hpp
#define Transition_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./Alphabet.hpp"

namespace llvmadt{
class State;
class Transition
{
protected:
    State* fromState;
    Letter* letter;
    State* toState;
public:
    Transition(/* args */);
    ~Transition();
};

}
#endif