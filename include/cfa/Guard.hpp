#ifndef Guard_hpp
#define Guard_hoo
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <z3++.h>

namespace llvmadt{
// Guard for the CFAEdge, where currently is a z3 expression converted from the LLVM IR
class Guard
{
private:
    z3::expr* guardExpr;
public:
    Guard();
    ~Guard();
    std::string& getGuardStr();
    void setGuard(z3::expr* expr);
    std::string toString();
    z3::expr* getExpr();
};

}

#endif
