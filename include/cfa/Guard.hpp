#ifndef Guard_hpp
#define Guard_hoo
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <z3++.h>

namespace llvmadt{
class Guard
{
private:
    z3::expr* guardExpr;
public:
    Guard();
    ~Guard();
    std::string getGuardStr();
    void setGuard(z3::expr* expr);
    std::string toString();
};

}

#endif
