#ifndef TestSampler_hpp
#define TestSampler_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include <map>
#include <ctime>
#include "../abstract/Automaton.hpp"
#include "../abstract/Path.hpp"

namespace llvmadt{
class TestSampler
{
private:
    Automaton* automaton;
    int K;
public:
    TestSampler(/* args */);
    TestSampler(Automaton* automaton);
    ~TestSampler();
    Automaton* getAutomaton();
    void setAutomaton(Automaton* automaton);
    Path* samplePathEven(State* startState);

    // typedef std::vector<State<A>*> PathVector;
    int getSampleNum();
    void setSampleNum();
    typedef std::map<State*, int> VisitCount;
    typedef std::vector<Transition* > succTrans;
    bool recursiveSort(State* currState, Path* path, VisitCount Count);
    // std::vector<State<A>* > Sample(State<A>* startState);

};


}
#endif