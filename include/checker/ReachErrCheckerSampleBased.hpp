#ifndef ReachErrCheckerSampleBased_hpp
#define ReachErrCheckerSampleBased_hpp
#include <stdlib.h>
#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <z3++.h>
#include "./PathChecker.hpp"
#include "./CheckerSampleBased.hpp"
#include "../automata/util/PathSampler.hpp"
#include "../automata/abstract/Automaton.hpp"
#include "../automata/dfa/DFA.hpp"
#include "./parser/SVCompParser.hpp"
#include "../converter/Converter.hpp"

namespace llvmadt
{
    class ReachErrCheckerSampleBased
    {
    private:
        /* data */
        PathChecker* pathChecker;
        PathSampler* pathSampler;
        std::set<std::string> varNames;
        Automaton* automaton;
        TLUtil* tlutil;
        z3::context* ctx;
        SVCompParser svParser;
    public:
        ReachErrCheckerSampleBased();
        ~ReachErrCheckerSampleBased();
        Path* checkReachError(std::string yamlPath, int sampleNum);
    };
    
    
    
} // namespace llvmadt


#endif