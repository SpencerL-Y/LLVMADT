#ifndef CheckerSampleBased_hpp
#define CheckerSampleBased_hpp
#include <stdlib.h>
#include <vector>
#include <list>
#include <set>
#include <iostream>
#include "./PathChecker.hpp"
#include "../automata/util/PathSampler.hpp"
#include "../automata/abstract/Automaton.hpp"
#include "../automata/dfa/DFA.hpp"

namespace llvmadt
{
class CheckerSampleBased
{
private:
    PathChecker* pathChecker;
    std::set<std::string> varNames;
    Automaton* automaton;

public:
    CheckerSampleBased(PathChecker* pathChecker, std::set<std::string> varName);
    void setAutomaton(DFA* dfa);
    PathChecker* getPathChecker();
    std::set<std::string> getVarNames();
    bool checkProperty()
    ~CheckerSampleBased();
}; // namespace llvmadt

}

 

#endif