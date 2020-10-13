#include "../../../include/automata/dfa/DFAState.hpp"

namespace llvmadt{
    
    void DFAState::addTransition(Transition* tran){
        if(tran->getFromState()->getId() == this->id && 
           tran->getAlphabet() == this->alphabet &&
           !this->hasTransition(tran->getFromState()->getId(), tran->getLetter(), tran->getToState()->getId())
           ){
               this->stateTransitions.insert(tran);
           }
           else {
               std::cout << "add transition error" << std::endl;
           }
    }
    
    void DFAState::delTransition(int from, Letter* l, int to){
        if(!this->hasTransition(from, l, to)){
            std::cout << "error del transition, transition not exist" << std::endl;
            return;
        }
        for(Transition* tran : this->stateTransitions){
            if(from == tran->getFromState()->getId() &&
               to == tran->getToState()->getId()&&
               l->getId() == tran->getLetter()->getId()){
                this->stateTransitions.erase(tran);
                delete(tran);
                return;
            }
        }
    }

    void DFAState::delTransition(Transition* tran){
        if(!this->hasTransition(tran->getFromState()->getId(), tran->getLetter(), tran->getToState()->getId())){
            std::cout << "error del transition, transition not exist" << std::endl;
            return;
        }
        this->stateTransitions.erase(tran);
        delete(tran);
    }

    
    std::string DFAState::toString(){
        std::string outStr = "";
        outStr += "DFAState ";
        outStr += this->getId();
        outStr += "\n";
        return outStr;
    }

    
    DFAState::DFAState(Alphabet* alphabet){
        this->alphabet = alphabet;
    }

    
    DFAState::DFAState(){

    }

    
    DFAState::~DFAState(){

    }

    
    DFAState* DFAState::executeLetter(Letter* l){
        if(this->alphabet != l->getAlphabet()){
            std::cout << "execute error, alphabet inconsistent" << std::endl;
            return nullptr;
        }
        for(Transition* tran : this->stateTransitions){
            if(tran->getLetter()->getId() == l->getId()){
                return (DFAState*)tran->getToState();
            }
        }
        return nullptr;
    }
}
