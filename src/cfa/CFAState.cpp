#include "../../include/cfa/CFAState.hpp"


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

void CFAState::addEdge(int fromId, int toId){
    if(this->getCfa()->getEdge(fromId, toId) == nullptr){
        CFAEdge* edge = new CFAEdge();
        edge->setFromState(this->getCfa()->getState(fromId));
        edge->setToState(this->getCfa()->getState(toId));
        this->edges.push_front(edge);
        this->getEdges().push_front(edge);
    } else {
        std::cout << "Error: add edge error, edge exists" << std::endl;
    }
}