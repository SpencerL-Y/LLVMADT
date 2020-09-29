#ifndef PathSampler_hpp
#define PathSampler_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../abstract/Automaton.hpp"
#include "../abstract/Path.hpp"

namespace llvmadt{
template <class A>
class PathSampler
{
private:
    Automaton<A>* automaton;
public:
    PathSampler(/* args */);
    PathSampler(Automaton<A>* automaton);
    ~PathSampler();
    Automaton<A>* getAutomaton();
    void setAutomaton(Automaton<A>* automaton);
    Path<A>* samplePathEven(State<A>* startState);
};


}
#endif