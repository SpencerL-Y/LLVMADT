#include "../../../include/automata/alphabet/LetterTypeZ3Expr.hpp"

namespace llvmadt{
    LetterTypeZ3Expr::LetterTypeZ3Expr(){

    }

    LetterTypeZ3Expr::~LetterTypeZ3Expr(){
        delete(this->expression);
    }

    std::string LetterTypeZ3Expr::toString(){
        return this->expression->to_string();
    }

    z3::expr* LetterTypeZ3Expr::getExpression(){
        return this->expression;
    }

    void LetterTypeZ3Expr::setExpression(z3::expr* expr){
        if(this->expression != nullptr){
            delete(this->expression);
        }
        this->expression = expr;
    }
}