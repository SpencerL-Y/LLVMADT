#include "../../include/cfa/Guard.hpp"


namespace llvmadt{
    std::string Guard::getGuardStr(){
        // std::cout << "gs: " << guardStr << '\n';
        return nullptr;
    }

    void Guard::setGuard(llvm::Instruction* inst){
        this->instruction = inst;
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
