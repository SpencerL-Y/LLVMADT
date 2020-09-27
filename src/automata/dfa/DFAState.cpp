#include "../../../include/automata/dfa/DFAState.hpp"

namespace llvmadt{
    template <class A>
    void DFAState<A>::addTransition(Transition<A>* tran){
        if(tran->getFromState()->getId() == this->id && 
           tran->getAlphabet() == this->alphabet &&
           !this->hasTransition(tran->getFromState()->getId(), tran->getLetter(), tran->getToState()->getId())
           ){
               this->stateTransitions.push_back(tran);
           }
    }
    template <class A>
    void DFAState<A>::delTransition(int from, Letter<A>* l, int to){
        if(!this->hasTransition(from, l, to)){
            std::cout << "error del transition, transition not exist" << std::endl;
            return;
        }
        int eraseId = 0;
        for(Transition<A>* tran : this->stateTransitions){
            if(from == tran->getFromState()->getId() &&
               to == tran->getToState()->getId()&&
               l->getId() == tran->getLetter()->getId()){
                    this->stateTransitions.erase(eraseId);
                    return;
               }
            eraseId++;
        }
    }

    template <class A>
    std::string DFAState<A>::toString(){
        std::string outStr = "";
        outStr += "DFAState " + this->getId() + "\n";
        return outStr;
    }

    template <class A>
    DFAState<A>::DFAState(Alphabet<A>* alphabet){
        this->alphabet = alphabet;
    }

    template <class A>
    DFAState<A>::DFAState(){

    }

    template <class A>
    DFAState<A>::~DFAState(){

    }

    template <class A>
    DFAState<A>* DFAState<A>::executeLetter(Letter<A>* l){
        if(this->alphabet != l->getAlphabet()){
            std::cout << "execute error, alphabet inconsistent" << std::endl;
            return nullptr;
        }
        for(Transition<A>* tran : this->stateTransitions){
            if(tran->getLetter()->getId() == l->getId()){
                return tran->getToState();
            }
        }
        return nullptr;
    }
}
