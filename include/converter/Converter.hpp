#ifndef Converter_hpp
#define Converter_hpp
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/IR/CFG.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm-10/llvm/ADT/AllocatorList.h"

#include "../cfa/CFA.hpp"
#include "../automata/Automaton.hpp"
namespace llvmadt{
class Converter
{
private:
    /* data */
public:
    Converter(/* args */){

    }
    ~Converter(){

    }
    std::list<CFA*> convertLLVM2CFAs(std::string ll_path);

    static Automaton* convertLTLf2DFA(std::string ltlf);

    static Automaton* convertLTL2BA(std::string ltl);
};
}
#endif
