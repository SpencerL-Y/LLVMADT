#ifndef SRC_TRANSLATOR_H_
#define SRC_TRANSLATOR_H_

#include <stdio.h>
#include <map>
#include <set>
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

#include "../automata/abstract/Path.hpp"
#include "z3++.h"

namespace llvmadt{

// typedef std::map<std::string, std::string>;


class Translator {
    protected:
        std::set<std::string> variableNames;
        std::map<std::string, int> varIndex; // (var, index)

    public:

        typedef std::map<std::string, std::string> BBMap;
   
        z3::expr* extractConstraints(llvm::Instruction* I, z3::context* C, Path* path);

        
        z3::expr* extractStore(const llvm::StoreInst *SI, z3::context *C, Path* path);
        z3::expr* extractLoad(const llvm::LoadInst *LI, z3::context *C, Path* path);
        z3::expr* extractBinaryOperator(const llvm::BinaryOperator *inst, z3::context *C, Path* path);
        z3::expr* extractCmp(const llvm::ICmpInst *CI, z3::context *C, Path* path);
        z3::expr* extractPHI(const llvm::PHINode *PHInst, z3::context *C, Path* path);

        z3::expr* extractTBranch(llvm::Instruction *brInst, std::string nexBBName, z3::context *C, Path* path);

        std::string toString(const llvm::Value *v);
        std::string getName(const llvm::Value *v);

        void extractVarName(llvm::Instruction* I);
        void extractAlloca(const llvm::AllocaInst  *AI);
        void extractStoreVar(const llvm::StoreInst *SI);

        void setVar(std::string varName);
        std::set<std::string> getVar();

        // void setVarIndex(std::map<std::string, int>* varIndex);
        // std::map<std::string, int>& getIndex();

        bool isNum(std::string str); 

        // z3::context &getContext(z3::config cfg) { return C(cfg); }
        // z3::context C;
        // // z3::expr_vector L;

};

}
#endif