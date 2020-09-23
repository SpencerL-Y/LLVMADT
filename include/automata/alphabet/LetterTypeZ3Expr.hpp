#ifndef LetterTypeZ3Expr_hpp
#define LetterTypeZ3Expr_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./LetterType.hpp"
#include "z3++.h"

namespace llvmadt{

class LetterTypeZ3Expr : public LetterType
{
private:
    z3::expr* expression;
public:
    std::string toString();
    z3::expr* getExpression();
    void setExpression(z3::expr* expr);
    LetterTypeZ3Expr(/* args */);
    ~LetterTypeZ3Expr();
};


}
#endif