#include "../../../include/automata/abstract/Automaton.hpp"


namespace llvmadt{
template <class A>
Automaton<A>::Automaton(/* args */)
{
    
}
template <class A>
Automaton<A>::~Automaton()
{
    for(Transition<A>* t : this->transitions){
        delete(t);
    }

    for(State<A>* s : this->states){
        delete(s);
    }
}

template <class A>
Automaton<A>::Automaton(Alphabet<A>* alphabet){
    this->alphabet = alphabet;
}



template <class A>
Alphabet<A>* Automaton<A>::getAlphabet(){
    return this->alphabet;
}


template <class A>
void Automaton<A>::setAlphabet(Alphabet<A>* alphabet){
    this->alphabet = alphabet;
}

template <class A>
std::string Automaton<A>::getName(){
    return this->name;
}

template <class A>
void Automaton<A>::setName(std::string name){
    this->name = name;
}


template <class A>
bool Automaton<A>::hasState(int id){
    for(State<A>* s : this->states){
        if(s->getId() == id){
            return true;
        }
    }
    return false;
}



template <class A>
State<A>* Automaton<A>::getState(int id){
    for(State<A>* s : this->states){
        if(s->getId() == id){
            return s;
        }
    }
    return nullptr;
}

template <class A>
bool Automaton<A>::hasTransition(int from, Letter<A>* l, int to){
    return this->getState(from)->hasTransition(from, l, to);
}
}