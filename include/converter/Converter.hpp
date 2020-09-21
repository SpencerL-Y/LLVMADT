#ifndef Converter_hpp
#define Converter_hpp
#include <stdlib.h>
#include <iostream>
#include <string>
#include <list>
#include <vector>
#include "../cfa/CFA.hpp"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/IR/BasicBlock.h"
#include "llvm/IR/Instruction.h"
#include "llvm/IRReader/IRReader.h"
#include "llvm/Support/SourceMgr.h"
#include "llvm/Support/raw_ostream.h"
class Converter
{
private:
    /* data */
public:
    Converter(/* args */);
    ~Converter();
    static std::list<CFA*> convertLLVM2CFAs(std::string ll_path){
        LLVMContext context;
        SMDiagnostic err;
        std::unique_ptr<Module> Mod = parseIRFile(ll_path, err, context);
        if(!Mod){
            std::cout << "Error: Module is null, please check" << std::endl;
        }
        int functionId = 0;
        for(Module::iterator m_iter = Mod->begin(); m_iter != Mod->end(); ++m_iter){
            CFA currCFA;
            Function* currFunc = &*m_iter;
            currCFA.setName("Func_" + functionId);
            int stateId = 0;
            //Add states
            for(Function::iterator f_iter = currFunc->begin(); f_iter != currFunc->end(); ++f_iter){
                BasicBlock* bb = &*f_iter;
                currCFA.addBlock(stateId);
                //TODO: more specific translation of instruction to the condition on the edge
                Instruction* lastInst;
                for(BasicBlock::iterator b_iter = bb->begin(); b_iter != bb->end(); ++b_iter){
                    lastInst = &*b_iter;
                    Instruction* currInst = &*b_iter;

                    //TODO: specify relation between state and instruction here

                    //TODO: add state increasing logic here.
                }
            }

            //Add edges
            for(Function::iterator f_iter = currFunc->begin(); f_iter != currFunc->end(); ++f_iter){
                BasicBlock* bb = &*f_iter;
                for(BasicBlock* succ : successors(bb)){
                    
                }
            }
            functionId ++;
        }
    }

    static Automaton* convertLTLf2DFA(std::string ltlf);

    static Automaton* convertLTL2BA(std::string ltl);
};

#endif