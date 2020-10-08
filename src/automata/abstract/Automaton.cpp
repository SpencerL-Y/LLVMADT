#include "../../../include/automata/abstract/Automaton.hpp"


namespace llvmadt{

Automaton::Automaton(/* args */)
{
    
}

Automaton::~Automaton()
{
    for(Transition* t : this->transitions){
        delete(t);
    }

    for(State* s : this->states){
        delete(s);
    }
}


Automaton::Automaton(Alphabet* alphabet){
    this->alphabet = alphabet;
}




Alphabet* Automaton::getAlphabet(){
    return this->alphabet;
}



void Automaton::setAlphabet(Alphabet* alphabet){
    this->alphabet = alphabet;
}


std::string Automaton::getName(){
    return this->name;
}


void Automaton::setName(std::string name){
    this->name = name;
}



bool Automaton::hasState(int id){
    for(State* s : this->states){
        if(s->getId() == id){
            return true;
        }
    }
    return false;
}




State* Automaton::getState(int id){
    for(State* s : this->states){
        if(s->getId() == id){
            return s;
        }
    }
    return nullptr;
}


bool Automaton::hasTransition(int from, Letter* l, int to){
    return this->getState(from)->hasTransition(from, l, to);
}
}