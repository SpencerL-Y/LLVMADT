#ifndef PathChecker_hpp
#define PathChecker_hpp

#include <stdlib.h>
#include <vector>
#include <list>
#include <iostream>
#include <z3++.h>
#include <spot/tl/parse.hh>
#include "../automata/abstract/Path.hpp"
#include "../automata/alphabet/LetterTypeZ3Expr.hpp"
#include "../automata/alphabet/LetterType.hpp"
#include "../logic/util/TLUtil.hpp"
namespace llvmadt
{
    // path checker is used for checking the feasibility of a path in the CFG of the program 
    // or check whether a sample program trace satisfy a ltl property
    class PathChecker
    {
    private:
        /* data */
        TLUtil* tlutil;
    public:
        PathChecker(/* args */TLUtil* ut, z3::context* c);
        ~PathChecker();

        z3::solver* checkFinitePathFeasibility(Path* path);
        bool checkFinitePathProperty(Path* path, std::string ltlStr, std::set<std::string> varNames);
        void addTLUtilApStrMap(std::string apStr, z3::expr* exp);
    };
    
    
    
} // namespace llvmadt


#endif