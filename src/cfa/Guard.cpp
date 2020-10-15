#include "../../include/cfa/Guard.hpp"


namespace llvmadt{
    std::string Guard::getGuardStr(){
        std::string guardStr = this->guardExpr->to_string();
        // std::cout << "gs: " << guardStr << '\n';
        return guardStr;
    }

    void Guard::setGuard(z3::expr* expr){
        this->guardExpr = expr;
    }

    std::string Guard::toString(){
        std::string str = this->getGuardStr();
        return str;
    }

    llvm::Instruction* Guard::getInstruction(){
        return this->instruction;
    }
    
    Guard::Guard(){
        this->instruction = nullptr;
    }

    Guard::~Guard(){

    }

}
