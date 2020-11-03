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
protected:
    PathChecker* pathChecker;
    PathSampler* pathSampler;
    std::set<std::string> varNames;
    Automaton* automaton;
    TLUtil* tlutil;
    z3::context* ctx;


public:
    CheckerSampleBased(PathSampler* pathSampler, std::set<std::string> varName, z3::context* c);
    void setAutomaton(DFA* dfa);
    PathChecker* getPathChecker();
    std::set<std::string>& getVarNames();
    Automaton* getAutomaton();
    TLUtil* getTlUtil();
    void setAutomaton(Automaton* automaton);
    void addBind(std::string ltlAp, z3::expr* expr);

    Path* checkProperty(std::string spotLTLStr, int pathNum, z3::context* ctx);
    ~CheckerSampleBased();
}; // namespace llvmadt

}

 

#endif