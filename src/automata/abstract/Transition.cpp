#include "../../../include/automata/abstract/Transition.hpp"


namespace llvmadt{
    

Transition::Transition(Alphabet* Alphabet){
    this->alphabet = alphabet;
}



Transition::Transition(State* from, Letter* l, State* to){
    this->fromState = from;
    this->toState = to;
    this->letter = l;
    this->alphabet = l->getAlphabet();
}



Transition::Transition(){

}



Transition::~Transition(){

}



Alphabet* Transition::getAlphabet(){
    return this->alphabet;
}



State* Transition::getFromState(){
    return this->fromState;
}



State* Transition::getToState(){
    return this->toState;
}



Letter* Transition::getLetter(){
    return this->letter;
}



}