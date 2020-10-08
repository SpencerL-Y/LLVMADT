#include "../../../include/automata/dfa/DFATrans.hpp"

namespace llvmadt{
    
    DFATrans::DFATrans(){

    }
    
    DFATrans::DFATrans(Alphabet* alphabet){
        this->alphabet = alphabet;
    }

    
    DFATrans::DFATrans(State* from, Letter* l, State* to){
        this->fromState = (State*)from;
        this->letter = l;
        this->toState = (State*)to;
        this->alphabet = l->getAlphabet();
    }
    

    DFATrans::~DFATrans(){
        
    }
}