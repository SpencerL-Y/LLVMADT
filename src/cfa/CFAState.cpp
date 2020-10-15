#include "../../include/cfa/CFAState.hpp"


namespace llvmadt{
int CFAState::getId(){
    return this->id;
}

void CFAState::setId(int id){
    this->id = id;
}


std::string CFAState::getBbName(){
    return this->bbName;
}

void CFAState::setBbName(std::string bbName){
    this->bbName = bbName;
}

std::string CFAState::toString(){
    return nullptr;
}

void CFAState::addEdge(CFAEdge* edge){
    this->edges.push_back(edge);
}

std::list<CFAEdge*>& CFAState::getEdges(){
    return this->edges;
}

bool CFAState::isBlockFinal(){
    return this->blockFinal;
}

void CFAState::setBlockFinal(bool final){
    this->blockFinal = final;
}


CFAState::CFAState(/* args */)
{
    
}

CFAState::~CFAState()
{
    std::cout << "delete state\n";  
}

CFA* CFAState::getCfa(){
    return this->cfa;
}
}