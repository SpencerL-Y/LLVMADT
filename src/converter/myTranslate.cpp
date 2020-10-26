#include <llvm/IR/BasicBlock.h>
#include <llvm/IR/IntrinsicInst.h>
#include "llvm/Support/raw_ostream.h"

#include "../../include/converter/myTranslate.hpp"

using namespace llvm;

namespace llvmadt{

z3::expr* Translator::extractConstraints(Instruction *I, z3::context *C, Path* path)
{
    // llvm::errs() << "extract from : " << *I << '\n';
    // z3::expr insExp;
    // z3::expr* E; // = new z3::expr(*C);
    // *E = C->bool_val(true);
    if(const AllocaInst *AI = dyn_cast<AllocaInst>(I))
    {
        // extractAlloca(AI);
        z3::expr* E = new z3::expr(*C);
        *E = C->bool_val(true);
        path->appendVarIndexArray(path->getVarIndex());
        return E;
    }

    // for (const Value *Op: I->operands())
    // {
    //     if (const GlobalValue* G = dyn_cast<GlobalValue>(Op))
    //     {
    //         errs() << "G getName: " << G->getName() << "\n";

    //     }
    // }

    // store
    if (const StoreInst *SI = dyn_cast<StoreInst>(I))
    {
       return extractStore(SI, C, path);
    }

    // %tmp = load %x
    if (const LoadInst *LI = dyn_cast<LoadInst>(I))
    {
        return extractLoad(LI, C, path);
    }

    //  binary operations
    // (opcodeName, opcode):(add,13) (sdiv, 20) 
    if (const BinaryOperator *inst = dyn_cast<BinaryOperator>(I))
    {
        return extractBinaryOperator(inst, C, path);
    }

    // cmp
    // %cmp = icmp sgt i32 %tmp, 0
    if (const ICmpInst *CI = dyn_cast<ICmpInst>(I))
    {
        return extractCmp(CI, C, path);
    }

    //std::cout << *E << '\n';
    // return E;
}

void Translator::extractVarName(Instruction *I)
{
    if(const AllocaInst *AI = dyn_cast<AllocaInst>(I))
    {
        extractAlloca(AI);
    }
    if (const StoreInst *SI = dyn_cast<StoreInst>(I))
    {
       extractStoreVar(SI);
    }
}

void Translator::extractAlloca(const AllocaInst *AI)
{
    std::string varName = AI->getName();
    setVar(varName);
}

void Translator::extractStoreVar(const StoreInst *SI)
{
    const Value *To = SI->getPointerOperand();
    std::string toNameStr = To->getName();
    setVar(toNameStr);
}

// store "From" "to"
// store 0 *%x
z3::expr* Translator::extractStore(const StoreInst *SI, z3::context *C, Path* path)
{
    const Value *From = SI->getValueOperand();
    const Value *To = SI->getPointerOperand();
    const Type *type = From->getType();

    std::string toNameStr = To->getName();
    std::string fromNameStr = getName(From);

    setVar(toNameStr);

    // std::cout << "toNameStr: " << toNameStr << '\n';

    // std::map<std::string, int>* varIndex =  &getIndex(); //new std::map<std::string, int>;
    // *varIndex = getIndex();
    // int count =  (this->varIndex).count(toNameStr);
    // if (count != 0)
    // {
    //     int index = (this->varIndex).find(toNameStr)->second + 1;      
    //     (this->varIndex).erase(toNameStr);
    //     (this->varIndex).insert(make_pair(toNameStr, index));
    //     // std::cout << "kkk store var index: " << (this->varIndex).find(toNameStr)->first << " " <<   (this->varIndex).find(toNameStr)->second << '\n';
    // }
    // else
    // {
    //     // std::cout << "count: " << count << '\n';
    //     (this->varIndex).insert(make_pair(toNameStr, 0));
    //     // std::cout << "store var index: " <<  (this->varIndex).find(toNameStr)->first << " " <<  (this->varIndex).find(toNameStr)->second << '\n';
    //     // std::cout << "countcount : " << (this->varIndex).count(toNameStr) << '\n';
    // }
    
    path->insertVarIndex(toNameStr);

    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);

    // std::string index = std::to_string( (this->varIndex).find(toNameStr)->second);
    std::string index = std::to_string(path->getVarIndexVarName(toNameStr));
    
    // map<srcVar, currIndex>
    // int intIndex = path->getVarIndexVarName(toNameStr);
    path->appendVarIndexArray(path->getVarIndex());
    
    toNameStr = toNameStr + "_" + index;

    // std::cout << "h" << '\n';
    z3::expr Sop1 = C->int_const(toNameStr.data());
    z3::expr Sop2 = C->int_const(fromNameStr.data());
    if (isNum(fromNameStr))
    {
        // std::cout << "int: " << secValue << '\n';
        Sop2 = C->int_val(std::stoi(fromNameStr));
        // std::cout << "int Lop2: " << secValue.data() << '\n';
    }
    else
    {
        // std::string indexFrom = std::to_string( (this->varIndex).find(fromNameStr)->second);
        std::string indexFrom = std::to_string(path->getVarIndexVarName(fromNameStr));
        fromNameStr = fromNameStr + "_" + indexFrom;
        Sop2 = C->int_const(fromNameStr.data());
    }
    

    *E = Sop1 == Sop2;
    // std::cout << "hh" << '\n';
    std::cout << "store expr: " << (*E).to_string() << '\n';
    return E;

    // errs() << "Store MStr[]: toNameStr: " << toNameStr << " fromNameStr: " << fromNameStr << '\n'; 
    // errs() << *SI << '\n';
}

z3::expr* Translator::extractLoad(const LoadInst *LI, z3::context *C, Path* path)
{
    // %tmp
    std::string Lop1Name = LI->getName();

    // %x
    const Value *From = LI->getPointerOperand();
    std::string Lop2Name = From->getName();

    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);

    // std::map<std::string, int>* varIndex =  &getIndex();
    // int count =  (this->varIndex).count(Lop1Name);
    // if (count != 0)
    // {
    //     int index = (this->varIndex).find(Lop1Name)->second + 1;      
    //     (this->varIndex).erase(Lop1Name);
    //     (this->varIndex).insert(make_pair(Lop1Name, index));
    //     // std::cout << "kkk store var index: " << (this->varIndex).find(toNameStr)->first << " " <<   (this->varIndex).find(toNameStr)->second << '\n';
    // }
    // else
    // {
    //     // std::cout << "count: " << count << '\n';
    //     (this->varIndex).insert(make_pair(Lop1Name, 0));
    //     // std::cout << "store var index: " <<  (this->varIndex).find(toNameStr)->first << " " <<  (this->varIndex).find(toNameStr)->second << '\n';
    //     // std::cout << "countcount : " << (this->varIndex).count(toNameStr) << '\n';
    // }

    path->insertVarIndex(Lop1Name);
    path->appendVarIndexArray(path->getVarIndex());

    // std::string index1 = std::to_string( (this->varIndex).find(Lop1Name)->second);
    std::string index1 = std::to_string(path->getVarIndexVarName(Lop1Name));
    // std::cout << "find index to z3: " << index << '\n'; 
    Lop1Name = Lop1Name + "_" + index1;

    // std::string index2 = std::to_string( (this->varIndex).find(Lop2Name)->second);
    std::string index2 = std::to_string(path->getVarIndexVarName(Lop2Name));
    Lop2Name = Lop2Name + "_" + index2;

    z3::expr Lop1 = C->int_const(Lop1Name.data());
    z3::expr Lop2 = C->int_const(Lop2Name.data());

    *E = Lop1 == Lop2;
    return E;
}

z3::expr* Translator::extractBinaryOperator(const BinaryOperator *inst, z3::context *C, Path* path)
{
    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);

    const Value *Op1 = inst->getOperand(0);
    const Value *Op2 = inst->getOperand(1);

    std::string BOName = inst->getName();
    std::string op1Name = getName(Op1);
    std::string op2Name = getName(Op2);

    // int count =  (this->varIndex).count(BOName);
    // if (count != 0)
    // {
    //     int index = (this->varIndex).find(BOName)->second + 1;      
    //     (this->varIndex).erase(BOName);
    //     (this->varIndex).insert(make_pair(BOName, index));
    //     // std::cout << "kkk store var index: " << (this->varIndex).find(toNameStr)->first << " " <<   (this->varIndex).find(toNameStr)->second << '\n';
    // }
    // else
    // {
    //     // std::cout << "count: " << count << '\n';
    //     (this->varIndex).insert(make_pair(BOName, 0));
    //     // std::cout << "store var index: " <<  (this->varIndex).find(toNameStr)->first << " " <<  (this->varIndex).find(toNameStr)->second << '\n';
    //     // std::cout << "countcount : " << (this->varIndex).count(toNameStr) << '\n';
    // }
    path->insertVarIndex(BOName);
    path->appendVarIndexArray(path->getVarIndex());

    // std::string index = std::to_string( (this->varIndex).find(BOName)->second);
    std::string index = std::to_string(path->getVarIndexVarName(BOName));

    // std::cout << "find index to z3: " << index << '\n'; 
    BOName = BOName + "_" + index;

    z3::expr BO = C->int_const(BOName.data());
    z3::expr BO1 = C->int_const(op1Name.data());
    z3::expr BO2 = C->int_const(op2Name.data());

    if (isNum(op1Name))
    {
        BO1 = C->int_val(std::stoi(op1Name));
    }
    else
    {
        // std::string indexOp1 = std::to_string( (this->varIndex).find(op1Name)->second);
        std::string indexOp1 = std::to_string(path->getVarIndexVarName(op1Name));
        
        // std::cout << "find index to z3: " << index << '\n'; 
        op1Name = op1Name + "_" + indexOp1;
        BO1 = C->int_const(op1Name.data());
    }
    
    if (isNum(op2Name))
    {
        BO2 = C->int_val(std::stoi(op2Name));
    }
    else
    {
        //std::string indexOp2 = std::to_string( (this->varIndex).find(op2Name)->second);
        std::string indexOp2 = std::to_string(path->getVarIndexVarName(op2Name));
        
        // std::cout << "find index to z3: " << index << '\n'; 
        op2Name = op2Name + "_" + indexOp2;
        BO2 = C->int_const(op2Name.data());
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

z3::expr* Translator::extractCmp(const ICmpInst *CI, z3::context *C, Path* path)
{
    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);

    const Value *Op1 = CI->getOperand(0);
    const Value *Op2 = CI->getOperand(1);
    // outs() << "cmp: " << II->getOpcodeName() << '\n';

    std::string op1Name = getName(Op1);
    std::string op2Name = getName(Op2);

    std::string CmpName = CI->getName();

    // int count =  (this->varIndex).count(CmpName);
    // if (count != 0)
    // {
    //     int index = (this->varIndex).find(CmpName)->second + 1;      
    //     (this->varIndex).erase(CmpName);
    //     (this->varIndex).insert(make_pair(CmpName, index));
    //     // std::cout << "kkk store var index: " << (this->varIndex).find(toNameStr)->first << " " <<   (this->varIndex).find(toNameStr)->second << '\n';
    // }
    // else
    // {
    //     // std::cout << "count: " << count << '\n';
    //     (this->varIndex).insert(make_pair(CmpName, 0));
    //     // std::cout << "store var index: " <<  (this->varIndex).find(toNameStr)->first << " " <<  (this->varIndex).find(toNameStr)->second << '\n';
    //     // std::cout << "countcount : " << (this->varIndex).count(toNameStr) << '\n';
    // }
    path->insertVarIndex(CmpName);
    path->appendVarIndexArray(path->getVarIndex());

    // std::string indexCmp = std::to_string( (this->varIndex).find(CmpName)->second);
    std::string indexCmp = std::to_string(path->getVarIndexVarName(CmpName)); 
        // std::cout << "find index to z3: " << index << '\n'; 
    CmpName = CmpName + "_" + indexCmp;

    z3::expr CMP = C->bool_const(CmpName.data());
    z3::expr OP1 = C->int_const(op1Name.data());
    z3::expr OP2 = C->int_const(op2Name.data());
    if (isNum(op1Name))
    {
        OP1 = C->int_val(std::stoi(op1Name));
    }
    else
    {
        // std::string indexOp1 = std::to_string( (this->varIndex).find(op1Name)->second);
        std::string indexOp1 = std::to_string(path->getVarIndexVarName(op1Name)); 
     
        // std::cout << "find index to z3: " << index << '\n'; 
        op1Name = op1Name + "_" + indexOp1; 
        OP1 = C->int_const(op1Name.data());
    }
    
    if (isNum(op2Name))
    {
        OP2 = C->int_val(std::stoi(op2Name));
    }
    else
    {
        // std::string indexOp2 = std::to_string( (this->varIndex).find(op2Name)->second);
        std::string indexOp2 = std::to_string(path->getVarIndexVarName(op2Name)); 
        // std::cout << "find index to z3: " << index << '\n'; 
        op2Name = op2Name + "_" + indexOp2; 
        OP2 = C->int_const(op2Name.data());
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

z3::expr* Translator::extractTBranch(Instruction *brInst, std::string nexBBName, z3::context *C, Path* path)
{
    path->appendVarIndexArray(path->getVarIndex());
    // llvm::errs() << "extract from : " << *brInst << '\n';
    // const Instruction *TTInst = curBB->getTerminator();
    z3::expr* E = new z3::expr(*C);
    *E = C->bool_val(true);
    // errs() << "TTInst: " << TTInst->getOperand(0)->getName() << '\n';
    if (const BranchInst *BI = dyn_cast<BranchInst>(brInst))
    {
        std::string BrName = BI->getOperand(0)->getName();
        // std::string indexBr = std::to_string( (this->varIndex).find(BrName)->second);
        std::string indexBr = std::to_string(path->getVarIndexVarName(BrName)); 
        // std::cout << "find index to z3: " << index << '\n'; 
        BrName = BrName + "_" + indexBr;

        if (BI->isConditional())
        {
            // // errs() << BrName << '\n';

            BasicBlock *TB = BI->getSuccessor(0);
            BasicBlock *FB = BI->getSuccessor(1);

            // if (nexBB->getName() == TB->getName())
            // {
            //     // E = C->int_const(BrName.data());
            //     *E = C->bool_const(BrName.data());
            // }
            // else if (nexBB->getName() == FB->getName())
            // {

            //     *E = !C->bool_const(BrName.data());
            // }
            if (nexBBName == TB->getName())
            {
                // E = C->int_const(BrName.data());
                *E = C->bool_const(BrName.data());
            }
            else if (nexBBName == FB->getName())
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

void Translator::setVar(std::string varName)
{
    this->variableNames.insert(varName);
}

std::set<std::string> Translator::getVar()
{
    return this->variableNames;
}

// void Translator::setVarIndex(std::map<std::string, int> *varIndex)
// {
//     std::cout << "set varIndex: " << varIndex << '\n';
//     this->varIndex = varIndex;
// }

// std::map<std::string, int>& Translator::getIndex()
// {
//     return this->varIndex;
// }

}


