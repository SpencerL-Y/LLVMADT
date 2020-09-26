#include "../../../include/automata/abstract/Transition.hpp"


namespace llvmadt{
    
template<class A>
Transition<A>::Transition(Alphabet<A>* Alphabet){
    this->alphabet = alphabet;
}


template<class A>
Transition<A>::Transition(State<A>* from, Letter<A>* l, State<A>* to){
    this->fromState = from;
    this->toState = to;
    this->letter = l;
    this->alphabet = l->getAlphabet();
}


template<class A>
Transition<A>::Transition(){

}


template<class A>
Transition<A>::~Transition(){

}


template<class A>
Alphabet<A>* Transition<A>::getAlphabet(){
    return this->alphabet;
}


template<class A>
State<A>* Transition<A>::getFromState(){
    return this->fromState;
}


template<class A>
State<A>* Transition<A>::getToState(){
    return this->toState();
}


template<class A>
Letter<A>* Transition<A>::getLetter(){
    return this->letter;
}



}