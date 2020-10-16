#ifndef CheckerSampleBased_hpp
#define CheckerSampleBased_hpp
#include <stdlib.h>
#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <z3++.h>
#include "./PathChecker.hpp"
#include "../automata/util/PathSampler.hpp"
#include "../automata/abstract/Automaton.hpp"
#include "../automata/dfa/DFA.hpp"
#include "../logic/util/TLUtil.hpp"

namespace llvmadt
{
class CheckerSampleBased
{
private:
    PathChecker* pathChecker;
    PathSampler* pathSampler;
    std::set<std::string> varNames;
    Automaton* automaton;
    TLUtil* tlutil;
    z3::context* ctx;


public:
    CheckerSampleBased(PathSampler* pathSampler, std::set<std::string> varName);
    void setAutomaton(DFA* dfa);
    PathChecker* getPathChecker();
    std::set<std::string>& getVarNames();
    Automaton* getAutomaton();
    void setAutomaton(Automaton* automaton);

    Path* checkProperty(std::string spotLTLStr, int pathNum);
    ~CheckerSampleBased();
}; // namespace llvmadt

}

 

#endif