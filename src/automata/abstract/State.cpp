#include "../../../include/automata/abstract/State.hpp"


namespace llvmadt{


int State::getId(){
    return this->id;
}


void State::setId(int id){
    this->id = id;
}



bool State::isAccState(){
    return this->isAccept;
}



void State::setAcc(){
    this->isAccept = true;
}



bool State::isInitialState(){
    return this->isInit;
}



void State::setInit(){
    this->isInit = true;
}



bool State::hasTransition(int from, Letter* l, int to){
    if(!(this->alphabet == l->getAlphabet())){
        std::cout << "error hasTransition, inconsistent alphabet" << std::endl; 
        return false;
    }
    for(Transition* e : this->stateTransitions){
        if(e->getFromState()->getId() == from &&
           e->getLetter()->getId() == l->getId()&& 
           e->getToState()->getId() == to){
               return true;
           }
    }
    return false;
}


Alphabet* State::getAlphabet(){
    return this->alphabet;
}



void State::setAlphabet(Alphabet* alpha){
    if(this->alphabet == nullptr){
        this->alphabet = alpha;
    } else if(this->alphabet != alpha){
        std::cout << "Alphabet exists, set error" << std::endl;   
    } else {
        
    }
    
}



State::State(){

}



State::State(Alphabet* alpha){
    this->alphabet = alpha;
}



State::~State(){

}


std::set<Transition*>& State::getStateTransitions(){
    return this->stateTransitions;
}

}
