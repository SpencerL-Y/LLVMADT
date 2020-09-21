#include "../../include/converter/Converter.hpp"



namespace llvmadt{
std::list<CFA*> Converter::convertLLVM2CFAs(std::string ll_path){
    llvm::LLVMContext context;
    llvm::SMDiagnostic err;
    std::unique_ptr<llvm::Module> Mod = parseIRFile(ll_path, err, context);
    if(!Mod){
        std::cout << "Error: Module is null, please check" << std::endl;
    }
    int functionId = 0;
    for(llvm::Module::iterator m_iter = Mod->begin(); m_iter != Mod->end(); ++m_iter){
        CFA currCFA;
        llvm::Function* currFunc = &*m_iter;
        currCFA.setName("Func_" + functionId);
        int stateId = 0;
        //Add states
        for(llvm::Function::iterator f_iter = currFunc->begin(); f_iter != currFunc->end(); ++f_iter){
            llvm::BasicBlock* bb = &*f_iter;
            currCFA.addState(stateId);
            //TODO: more specific translation of instruction to the condition on the edge
            llvm::Instruction* lastInst;
            for(llvm::BasicBlock::iterator b_iter = bb->begin(); b_iter != bb->end(); ++b_iter){
                lastInst = &*b_iter;
                llvm::Instruction* currInst = &*b_iter;

                //TODO: specify relation between state and instruction here

                //TODO: add state increasing logic here.
            }
        }

        //Add edges
        for(llvm::Function::iterator f_iter = currFunc->begin(); f_iter != currFunc->end(); ++f_iter){
            llvm::BasicBlock* bb = &*f_iter;
            for(llvm::BasicBlock* succ : successors(bb) ){
                
            }
        }
        functionId ++;
    }
}
}