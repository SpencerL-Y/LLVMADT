#include "../../include/cfa/CFA.hpp"

std::list<CFAState*> CFA::getStates(){
    return this->states;   
}

void CFA::setStates(std::list<CFAState*>& states){
    this->states = states;
}

int CFA::getStateNum(){
    return this->stateNum;
}

void CFA::addState(int id){
    for(CFAState* state : this->states){
        if(state->getId() == id){
            std::cout << "Error: add state error, id exists" << std::endl;
            return;
        }
    }
    CFAState* ns = new CFAState();
    ns->setId(id);
    this->states.push_front(ns);
}

void CFA::addState(CFAState* state){
    for(CFAState* state : this->states){
        if(state->getId() == state->getId()){
            std::cout << "Error: add state error, id exists" << std::endl;
            return;
        }
    }
    this->states.push_front(state);
}

CFAEdge* CFA::getEdge(int fromId, int toId){
    for(CFAEdge* edge : this->edges){
        if(edge->getFromState()->getId() == fromId &&
           edge->getToState()->getId() == toId){
               return edge;
           }
    }
    return nullptr;
}