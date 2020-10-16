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
#include "../../include/converter/myTranslate.hpp"
#include "../automata/alphabet/LetterType.hpp"
#include "../automata/alphabet/LetterTypeZ3Expr.hpp"
#include "../automata/alphabet/LetterTypeInt.hpp"
#include "../automata/alphabet/LetterTypeInst.hpp"
#include "../automata/alphabet/LetterTypeChar.hpp"
#include "z3++.h"
namespace llvmadt{
class PathSampler
{
private:
    Automaton* automaton;
    int K;
    int id;
public:
    PathSampler(/* args */);
    PathSampler(Automaton* automaton);
    ~PathSampler();
    Automaton* getAutomaton();
    void setAutomaton(Automaton* automaton);
    Path* samplePathEven(State* startState, z3::context* C);

    // typedef std::vector<State<A>*> PathVector;
    int getSampleNum();
    void setSampleNum();
    typedef std::map<State*, int> VisitCount;
    typedef std::vector<Transition* > succTrans;
    bool recursiveSort(State* currState, Path* path, VisitCount Count, z3::context* C);
    // std::vector<State<A>* > Sample(State<A>* startState);

};


}
#endif