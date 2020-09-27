#include "../../../include/automata/dfa/DFATrans.hpp"

namespace llvmadt{
    template <class A>
    DFATrans<A>::DFATrans(){

    }
    template <class A>
    DFATrans<A>::DFATrans(Alphabet<A>* alphabet){
        this->alphabet = alphabet;
    }

    template <class A>
    DFATrans<A>::DFATrans(DFAState<A>* from, Letter<A>* l, DFAState<A>* to){
        this->fromState = from;
        this->letter = l;
        this->toState = to;
        this->alphabet = l->getAlphabet();
    }
    template <class A>
    DFATrans<A>::~DFATrans(){
        
    }
}