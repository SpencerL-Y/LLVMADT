#ifndef LetterTypeInst_hpp
#define LetterTypeInst_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./LetterType.hpp"
#include <llvm/IR/Instruction.h>

namespace llvmadt
{
    class LetterTypeInst : public LetterType
    {
    private: 
        llvm::Instruction* inst;
    public:
        std::string toString();
        llvm::Instruction* getInstruction();
        void setInstruction(llvm::Instruction* inst);
        LetterTypeInst(/* args */);
        ~LetterTypeInst();
    };
    
} // namespace llvmadt


#endif