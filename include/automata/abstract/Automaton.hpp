#ifndef Automaton_hpp
#define Automaton_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./Alphabet.hpp"
#include "./State.hpp"
#include "./Transition.hpp"

namespace llvmadt{
class Automaton
{
protected:
    std::string name;
    std::list<State*> states;
    std::list<Transition*> transitions;
    Alphabet* alphabet;
public:
    void addState(int id);
    void delState(int id);
    void addTransition(int fromId, Letter* l,  int toId);
    void delTransition(int fromId, Letter* l, int toId);

    Automaton(/* args */);
    ~Automaton();
};

}


#endif