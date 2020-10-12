#ifndef SRC_TRANSLATOR_H_
#define SRC_TRANSLATOR_H_

#include <stdio.h>
#include <map>
#include <vector>
#include <list>
#include <ctime>
#include <iostream>
#include <sstream>
#include <string.h>
#include <stack>
#include <fstream>

#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IntrinsicInst.h>
#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IRReader/IRReader.h>
#include <llvm/Support/SourceMgr.h>

#include "llvm/AsmParser/Parser.h"
#include "llvm/IR/InstIterator.h"
#include "llvm/IR/Module.h"
#include "llvm/Support/SourceMgr.h"
#include <llvm/Analysis/CFG.h>

#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/Instructions.h"

#include "z3++.h"

namespace llvmadt{

// typedef std::map<std::string, std::string>;


class Translator {
    public:

        typedef std::stack<std::string> StoreStack;
        typedef std::map<std::string, std::stack<std::string>> StoreMap;

        typedef std::map<std::string, std::string> BBMap;
   
        z3::expr* extractConstraints(llvm::Instruction* I, StoreMap* MStr, z3::context* C);

        void extractStore(const llvm::StoreInst *SI, StoreMap *MStr);
        z3::expr* extractLoad(const llvm::LoadInst *LI,  StoreMap *MStr, z3::context *C);
        z3::expr* extractBinaryOperator(const llvm::BinaryOperator *inst, z3::context *C);
        z3::expr* extractCmp(const llvm::ICmpInst *CI, z3::context *C);
        z3::expr* extractTBranch(llvm::BasicBlock *curBB, llvm::BasicBlock *preSampleBB, z3::context *C);

        std::string toString(const llvm::Value *v);
        std::string getName(const llvm::Value *v);


        bool isNum(std::string str); 

        // z3::context &getContext(z3::config cfg) { return C(cfg); }
        // z3::context C;
        // // z3::expr_vector L;

};

}
#endif