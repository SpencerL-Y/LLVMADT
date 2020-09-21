#include "../../include/cfa/CFAState.hpp"


namespace llvmadt{
int CFAState::getId(){
    return this->id;
}

void CFAState::setId(int id){
    this->id = id;
}

void CFAState::setInstruction(CFAInstruction* instruction){
    if(this->instruction){
        delete(this->instruction);
    }
    this->instruction = instruction;
}

CFAInstruction* CFAState::getInstruction(){
    return this->instruction;
}

std::string CFAState::toString(){
    return nullptr;
}

void CFAState::addEdge(CFAEdge* edge){
    this->edges.push_back(edge);
}

CFAState::CFAState(/* args */)
{
    this->instruction = new CFAInstruction();
}

CFAState::~CFAState()
{
    delete(this->instruction);
}
}