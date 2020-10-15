#ifndef Guard_hpp
#define Guard_hoo
#include <stdlib.h>
#include <iostream>
#include <vector>
#include <list>
#include <llvm/IR/Instruction.h>

namespace llvmadt{
// Guard for the CFAEdge, where currently is a z3 expression converted from the LLVM IR
class Guard
{
private:
    llvm::Instruction* instruction;
public:
    Guard();
    ~Guard();
    std::string getGuardStr();
    void setGuard(llvm::Instruction* inst);
    std::string toString();
    llvm::Instruction* getInstruction();
};

}

#endif
