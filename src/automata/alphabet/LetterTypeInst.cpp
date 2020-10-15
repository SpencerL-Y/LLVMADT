#include "../../../include/automata/alphabet/LetterTypeInst.hpp"

namespace llvmadt
{
    
    LetterTypeInst::LetterTypeInst(/* args */)
    {
    }
    
    LetterTypeInst::~LetterTypeInst()
    {
        
    }
    std::string LetterTypeInst::toString(){
        return nullptr;
    }
    llvm::Instruction* LetterTypeInst::getInstruction(){
        return this->inst;
    }
    void LetterTypeInst::setInstruction(llvm::Instruction* inst){
        this->inst = inst;
    }
    
} // namespace llvmadt
