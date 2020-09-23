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

void CFAEdge::mkGuard(z3::expr expr){
    if(this->guard != nullptr){
        delete(this->guard);
    }
    Guard* g = new Guard();
    this->guard = g;
}

Guard* CFAEdge::getGuard(){
    return this->guard;
}

std::string CFAEdge::getGuardStr(){
    //TODO
    return nullptr;
}

std::string CFAEdge::toString(){
    //TODO
    return nullptr;
}

z3::context* CFAEdge::getContext(){
    return this->c;
}

void CFAEdge::setContext(z3::context* c){
    this->c = c;
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