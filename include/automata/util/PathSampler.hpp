#ifndef PathSampler_hpp
#define PathSampler_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../abstract/Automaton.hpp"
#include "../abstract/Path.hpp"

namespace llvmadt{

class PathSampler
{
private:
    Automaton* automaton;
public:
    PathSampler(/* args */);
    PathSampler(Automaton* automaton);
    ~PathSampler();
    Automaton* getAutomaton();
    void setAutomaton(Automaton* automaton);
    Path* samplePathEven(State* startState);
};


}
#endif