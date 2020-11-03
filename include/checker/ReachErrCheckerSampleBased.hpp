#ifndef ReachErrCheckerSampleBased_hpp
#define ReachErrCheckerSampleBased_hpp
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
    class ReachErrCheckerSampleBased
    {
    private:
        /* data */
    public:
        ReachErrCheckerSampleBased(/* args */);
        ~ReachErrCheckerSampleBased();
        Path* checkReachError(std::string yamlPath);
    };
    
    
    
} // namespace llvmadt


#endif