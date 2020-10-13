#include "../../../include/automata/alphabet/LetterTypeZ3Expr.hpp"

namespace llvmadt{
    LetterTypeZ3Expr::LetterTypeZ3Expr(){

    }

    LetterTypeZ3Expr::LetterTypeZ3Expr(z3::expr* expr, z3::context* context){
        if(expr == nullptr || context == nullptr){
            std::cout << "error null ptr z3Expr letter type" << std::endl;
        }
        this->context = context;
        this->expression = expr;
    }
    LetterTypeZ3Expr::~LetterTypeZ3Expr(){
        delete(this->expression);
    }

    std::string LetterTypeZ3Expr::toString(){
        return this->expression->to_string();
    }

    z3::context* LetterTypeZ3Expr::getContext(){
        return this->context;
    }

    z3::expr* LetterTypeZ3Expr::getExpression(){
        return this->expression;
    }

    void LetterTypeZ3Expr::setExpression(z3::expr* expr, z3::context* context){
        this->context = context;
        if(this->expression != nullptr){
            delete(this->expression);
        }
        this->expression = expr;
    }
}