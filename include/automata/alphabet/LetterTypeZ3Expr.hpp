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
    z3::context* context;
public:
    std::string toString();
    z3::expr* getExpression();
    z3::context* getContext();
    void setExpression(z3::expr* expr, z3::context* context);
    LetterTypeZ3Expr(/* args */);
    LetterTypeZ3Expr(z3::expr* expr, z3::context* context);
    LetterTypeZ3Expr(z3::context* context);
    ~LetterTypeZ3Expr();
    
};


}
#endif