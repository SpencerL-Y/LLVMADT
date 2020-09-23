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

std::list<CFAEdge*> CFAState::getEdges(){
    return this->edges;
}

bool CFAState::isBlockFinal(){
    return this->blockFinal;
}

void CFAState::setBlockFinal(bool final){
    this->blockFinal = final;
}

z3::context* CFAState::getContext(){
    return this->c;
}

void CFAState::setContext(z3::context* c){
    this->c = c;
}

CFAState::CFAState(/* args */)
{
    this->instruction = new CFAInstruction();
}

CFAState::~CFAState()
{
    std::cout << "delete state\n";  
    delete(this->instruction);
}
}