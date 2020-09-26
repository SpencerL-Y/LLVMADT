#include "../../../include/automata/abstract/State.hpp"


namespace llvmadt{

template<class A>
int State<A>::getId(){
    return this->id;
}

template<class A>
void State<A>::setId(int id){
    this->id = id;
}


template<class A>
bool State<A>::isAccState(){
    return this->isAccept;
}


template<class A>
void State<A>::setAcc(){
    this->isAccept = true;
}


template<class A>
bool State<A>::isInitialState(){
    return this->isInit;
}


template<class A>
void State<A>::setInit(){
    this->isInit = true;
}


template<class A>
Alphabet<A>* State<A>::getAlphabet(){
    return this->alphabet;
}


template<class A>
void State<A>::setAlphabet(Alphabet<A>* alpha){
    if(this->alphabet != nullptr){
        this->alphabet = alpha;
    } else {
        std::cout << "Alphabet exists, set error" << std::endl;   
    }
    
}


template<class A>
State<A>::State(){

}


template<class A>
State<A>::State(Alphabet<A>* alpha){
    this->alphabet = alpha;
}


template<class A>
State<A>::~State(){

}

template<class A>
std::list<Transition<A>*>& State<A>::getStateTransitions(){
    return this->stateTransitions;
}

}
