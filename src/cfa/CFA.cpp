#include "../../include/cfa/CFA.hpp"

namespace llvmadt{
std::list<CFAState*>& CFA::getStates(){
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
    state->setContext(this->c);
    this->states.push_front(state);
    this->stateNum ++;
}

CFAState* CFA::getState(int id){
    for(CFAState* state : this->states){
        if(state->getId() == id){
            return state;
        }
    }
    return nullptr;
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

std::list<CFAEdge*> CFA::getEdges(){
    return this->edges;
}

void CFA::addEdge(int fromId, int toId){
    if(this->hasStateId(fromId) && this->hasStateId(toId) && !this->hasEdgeId(fromId, toId)){
        CFAEdge* ne = new CFAEdge();
        ne->setFromState(this->getState(fromId));
        ne->setToState(this->getState(toId));
        ne->setContext(this->c);
        this->edges.push_front(ne);
        this->getState(fromId)->addEdge(ne);
    }
}




void CFA::addEdge(int fromId, z3::expr* guard_expr, int toId){
    if(this->hasStateId(fromId) && this->hasStateId(toId) && !this->hasEdgeId(fromId, toId)){
        CFAEdge* ne = new CFAEdge();
        ne->setFromState(this->getState(fromId));
        ne->setToState(this->getState(toId));
        ne->setContext(this->c);
        ne->mkGuard(guard_expr);
        this->edges.push_front(ne);
        this->getState(fromId)->addEdge(ne);
    }
}


bool CFA::hasStateId(int id){
    for(CFAState* state : this->states){
        if(state->getId() == id){
            return true;
        }
    }
    return false;
}

bool CFA::hasEdgeId(int fromId, int toId){
    for(CFAEdge* edge : this->edges){
        if(edge->getFromState()->getId() == fromId &&
           edge->getToState()->getId()   == toId){
               return true;
           }
    }
    return false;
}



void CFA::setName(std::string name){
    this->name = name;
}

std::string CFA::getName(){
    return this->name;
}

std::string CFA::toString(){
    //TODO: add later
    return nullptr;
}

void CFA::setContext(z3::context* c){
    this->c = c;
}

z3::context* CFA::getContext(){
    return this->c;
}

CFA::CFA(/* args */)
{
    this->c = new z3::context();
}

CFA::~CFA()
{
    for(CFAEdge* edge : this->getEdges()){
        delete(edge);
    }
    for(CFAState* state : this->states){
        delete(state);
    }
    delete(this->c);
}

}

