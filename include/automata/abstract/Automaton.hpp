#ifndef Automaton_hpp
#define Automaton_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../alphabet/Alphabet.hpp"
#include "./State.hpp"
#include "./Transition.hpp"
#include "./Word.hpp"
#include "./Path.hpp"
namespace llvmadt{
template <class A>
class Automaton
{
protected:
    std::string name;
    std::list<State<A>*> states;
    std::list<State<A>*> accStates;
    std::list<State<A>*> initState;
    std::list<Transition<A>*> transitions;
    Alphabet<A>* alphabet;
public:
    virtual void addState(int id)=0;
    virtual void addInitState(int id)=0;
    virtual void addAccState(int id)=0;
    virtual void delState(int id)=0;
    virtual void addTransition(int fromId, Letter<A>* l,  int toId)=0;
    virtual void delTransition(int fromId, Letter<A>* l, int toId)=0;
    virtual Path<A>* runOnWord(Word<A>* word)=0;
    virtual State<A>* getInitState()=0;
    virtual std::list<State<A>*> getAccStates()=0;
    void setName(std::string name);
    std::string getName();
    Alphabet<A>* getAlphabet();
    void setAlphabet(Alphabet<A>* alphabet);
    Automaton(/* args */);
    Automaton(Alphabet<A>* alphabet);
    ~Automaton();
};

}


#endif
