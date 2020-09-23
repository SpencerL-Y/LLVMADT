#ifndef Automaton_hpp
#define Automaton_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../alphabet/Alphabet.hpp"
#include "./State.hpp"
#include "./Transition.hpp"

namespace llvmadt{
template <class A>
class Automaton
{
protected:
    std::string name;
    std::list<State<A>*> states;
    std::list<Transition<A>*> transitions;
    Alphabet<A>* alphabet;
public:
    void addState(int id);
    void delState(int id);
    void addTransition(int fromId, Letter<A>* l,  int toId);
    void delTransition(int fromId, Letter<A>* l, int toId);

    Automaton(/* args */);
    ~Automaton();
};

}


#endif
