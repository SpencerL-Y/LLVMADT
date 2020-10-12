#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IntrinsicInst.h>
#include "llvm/Support/raw_ostream.h"

#include "../../include/converter/myTranslate.hpp"

using namespace llvm;

namespace llvmadt{

z3::expr* Translator::extractConstraints(Instruction *I,  StoreMap *MStr, z3::context *C)
{
    StoreMap *M = MStr;
    // z3::expr insExp;
    // store
    if (const StoreInst *SI = dyn_cast<StoreInst>(I))
    {
       extractStore(SI, M);
    }

    // %tmp = load %x
    if (const LoadInst *LI = dyn_cast<LoadInst>(I))
    {
        return extractLoad(LI, M, C);
    }

    //  binary operations
    // (opcodeName, opcode):(add,13) (sdiv, 20) 
    if (const BinaryOperator *inst = dyn_cast<BinaryOperator>(I))
    {
        return extractBinaryOperator(inst, C);
    }

    // cmp
    // %cmp = icmp sgt i32 %tmp, 0
    if (const ICmpInst *CI = dyn_cast<ICmpInst>(I))
    {
        return extractCmp(CI, C);
    }

    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);
    return E;
}

// store "From" "to"
// store 0 *%x
void Translator::extractStore(const StoreInst *SI, StoreMap *MStr)
{
    const Value *From = SI->getValueOperand();
    const Value *To = SI->getPointerOperand();
    const Type *type = From->getType();

    std::string toNameStr = To->getName();
    std::string fromNameStr = getName(From);

    StoreStack tmpToReg;
    tmpToReg.push(fromNameStr);

    // x: toNameStr        
    // if exist (x, stack"x"), push fromNameStr to stack"x"
    // else insert (x, tmpToReg)
    for(StoreMap::iterator Iter = MStr->begin(); Iter != MStr->end(); Iter++)
    {
        if (Iter->first == toNameStr)
        {
            Iter->second.push(fromNameStr);
        }
    }
    MStr->insert(std::make_pair(toNameStr, tmpToReg));

    // errs() << "Store MStr[]: toNameStr: " << toNameStr << " fromNameStr: " << fromNameStr << '\n'; 
    // errs() << *SI << '\n';
}

z3::expr* Translator::extractLoad(const LoadInst *LI,  StoreMap *MStr, z3::context *C)
{
    // %tmp
    std::string Lop1Name = LI->getName();

    // %x
    const Value *From = LI->getPointerOperand();
    std::string Lop2Name = From->getName();
    std::string secValue;

    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);
   
    // get value in %x
    for(StoreMap::iterator Iter = MStr->begin(); Iter != MStr->end(); Iter++)
    {
        // std::cout << Iter->first << " " << Iter->second << '\n';
        if (Lop2Name == Iter->first)
        {
            secValue = Iter->second.top();
            // std::cout << "second: " << Iter->second << '\n';
            z3::expr Lop1 = C->int_const(Lop1Name.data());
            z3::expr Lop2 = C->int_const(secValue.data());

            if (isNum(secValue))
            {
                // std::cout << "int: " << secValue << '\n';
                Lop2 = C->int_val(std::stoi(secValue));
                // std::cout << "int Lop2: " << secValue.data() << '\n';
            }

            *E = Lop1 == Lop2;
        }
    }
    return E;
}

z3::expr* Translator::extractBinaryOperator(const BinaryOperator *inst, z3::context *C)
{
    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);

    const Value *Op1 = inst->getOperand(0);
    const Value *Op2 = inst->getOperand(1);

    std::string BOName = inst->getName();
    std::string op1Name = getName(Op1);
    std::string op2Name = getName(Op2);

    z3::expr BO = C->int_const(BOName.data());
    z3::expr BO1 = C->int_const(op1Name.data());
    z3::expr BO2 = C->int_const(op2Name.data());

    if (isNum(op1Name))
    {
        BO1 = C->int_val(std::stoi(op1Name));
    }
    if (isNum(op2Name))
    {
        BO2 = C->int_val(std::stoi(op2Name));
    }

    if (inst->getOpcode() == Instruction:: Add)
    {
        *E = (BO == BO1 + BO2);
    }
    else if (inst->getOpcode() == Instruction:: Sub)
    {
        *E = (BO == BO1 - BO2);
    }

    else if (inst->getOpcode() == Instruction:: Mul)
    {
        *E = (BO == BO1 * BO2);
    }

    else if (inst->getOpcode() == Instruction:: SDiv)
    {
        *E = (BO == BO1 / BO2);
    }
    else
    {
        errs() << "have not support this BinaryOperator!" << '\n';
    }
    return E;
}

z3::expr* Translator::extractCmp(const ICmpInst *CI, z3::context *C)
{
    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);

    const Value *Op1 = CI->getOperand(0);
    const Value *Op2 = CI->getOperand(1);
    // outs() << "cmp: " << II->getOpcodeName() << '\n';

    std::string op1Name = getName(Op1);
    std::string op2Name = getName(Op2);

    std::string CmpName = CI->getName();
    
    z3::expr CMP = C->bool_const(CmpName.data());
    z3::expr OP1 = C->int_const(op1Name.data());
    z3::expr OP2 = C->int_const(op2Name.data());
    if (isNum(op1Name))
    {
        OP1 = C->int_val(std::stoi(op1Name));
    }
    if (isNum(op2Name))
    {
        OP2 = C->int_val(std::stoi(op2Name));
    }

    if (CI->getPredicate() == CmpInst::ICMP_EQ)
    {
        *E = (CMP == (OP1 == OP2));
    }
    else if (CI->getPredicate() == CmpInst::ICMP_NE)
    {
        *E = (CMP == OP1 != OP2);
    }
    else if (CI->getPredicate() == CmpInst::ICMP_SGT)
    {
        *E = (CMP == OP1 > OP2);
    }
    else if (CI->getPredicate() == CmpInst::ICMP_SGE)
    {
        *E = (CMP == OP1 >= OP2);
    }
    else if (CI->getPredicate() == CmpInst::ICMP_SLT)
    {
        *E = (CMP == OP1 < OP2);
    }
    else if (CI->getPredicate() == CmpInst::ICMP_SLE)
    {
        *E = (CMP == OP1 <= OP2);
    }
    else
    {
        errs() << "have not finished!" << '\n';
    }
    return E;    
}

z3::expr* Translator::extractTBranch(BasicBlock *curBB, BasicBlock *nexBB, z3::context *C)
{
    const Instruction *TTInst = curBB->getTerminator();
    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);
    // errs() << "TTInst: " << TTInst->getOperand(0)->getName() << '\n';
    if (const BranchInst *BI = dyn_cast<BranchInst>(TTInst))
    {
        if (BI->isConditional())
        {
            std::string BrName = BI->getOperand(0)->getName();
            // errs() << BrName << '\n';

            BasicBlock *TB = TTInst->getSuccessor(0);
            BasicBlock *FB = TTInst->getSuccessor(1);

            if (nexBB->getName() == TB->getName())
            {
                // E = C->int_const(BrName.data());
                *E = C->bool_const(BrName.data());
            }
            else if (nexBB->getName() == FB->getName())
            {

                *E = !C->bool_const(BrName.data());
            }
        }
    }
 
    return E;

}

std::string Translator::toString(const Value *v) 
{
    std::string Str;
    raw_string_ostream SS(Str);
    v->print(SS);
    // Str.erase(0, Str.find_first_not_of(WhiteSpaces));
    // return SS.str().substr(0, Str.find(" ="));
    return SS.str().substr(Str.find(" "), -1);
}

std::string Translator::getName(const Value *v)
{
    if (v->hasName())
    {
        // errs() << "toString: " << toString(v) << '\n';
        return v->getName();
    }
    else
    {
        return toString(v);
    }
    
}
// std::string Translator::toString(const Instruction* inst) {
//     std::string s;
//     raw_string_ostream os(s);
//     inst->print(os);
//     return os.str();
// }


bool Translator::isNum(std::string str)  
{  
    std::stringstream sin(str);  
    double d;  
    char c;  

    // true: double false: not num
    if(!(sin >> d))  
    {
        return false;
    }

    // get 34.f   
    if (sin >> c) 
    {
        return false;
    }  
    return true;  
}

}


