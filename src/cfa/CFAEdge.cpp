#include "../../include/cfa/CFAEdge.hpp"


namespace llvmadt{
CFAState* CFAEdge::getFromState(){
    return this->fromState;
}

CFAState* CFAEdge::getToState(){
    return this->toState;
}

void CFAEdge::setFromState(CFAState* fromState){
    this->fromState = fromState;
}

void CFAEdge::setToState(CFAState* toState){
    this->toState = toState;
}

void CFAEdge::mkGuard(llvm::Instruction* inst){
    if(this->guard != nullptr){
        delete(this->guard);
    }
    Guard* g = new Guard();
    g->setGuard(inst);
    this->guard = g;
}

Guard* CFAEdge::getGuard(){
    return this->guard;
}

std::string CFAEdge::getGuardStr(){
    std::string result = this->guard->getGuardStr();
    return nullptr;
}

CFAEdge::CFAEdge(/* args */)
{
    this->guard = new Guard();
}

CFAEdge::~CFAEdge()
{
    std::cout << "delete edge\n";  
    delete(this->guard);
}
}