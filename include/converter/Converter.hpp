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

#include <spot/tl/parse.hh>
#include <spot/twaalgos/translate.hh>
#include <spot/twaalgos/hoa.hh>
#include <spot/twaalgos/ltl2tgba_fm.hh>
#include <spot/twaalgos/sccfilter.hh>
#include <spot/twaalgos/minimize.hh>
#include <spot/twaalgos/stripacc.hh>
#include "../cfa/CFA.hpp"
#include "../automata/abstract/Automaton.hpp"
#include "../automata/buchi/BA.hpp"
#include "../automata/dfa/DFA.hpp"
#include "../automata/alphabet/Alphabet.hpp"
#include "../automata/alphabet/LetterType.hpp"
#include "../automata/alphabet/LetterTypeZ3Expr.hpp"
#include "../automata/alphabet/LetterTypeInt.hpp"
#include "../automata/alphabet/LetterTypeInst.hpp"
#include "../automata/alphabet/LetterTypeChar.hpp"
namespace llvmadt{

// converter is used for several conversion between data structures:
// 1.LTL, LTLf, TWA from spot
// 2.CFA
// 3.DFA, BA
class Converter
{
private:
    /* data */
   

public:
    Converter(/* args */){
    }
    ~Converter(){

    }

    std::list<CFA*> convertLLVM2CFAs( llvm::Module*  mod);

    Automaton* convertLTLf2DFA(std::string ltlf);

    Automaton* convertLTL2BA(std::string ltl);

    Automaton* convertCFA2DFA(CFA* cfa);

    Automaton* convertCFA2BA(CFA* cfa);

    Automaton* convertCFA2DFAReachError(CFA* cfa);
};
}
#endif
