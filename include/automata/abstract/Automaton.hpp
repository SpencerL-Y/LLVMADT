#ifndef Automaton_hpp
#define Automaton_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <set>
#include <vector>
#include "../alphabet/Alphabet.hpp"
#include "./State.hpp"
#include "./Transition.hpp"
#include "./Word.hpp"
#include "./Path.hpp"
namespace llvmadt{

class Automaton
{
protected:
    std::string name;
    std::set<State*> states;
    std::set<State*> accStates;
    State* initState;
    std::set<Transition*> transitions;
    Alphabet* alphabet;
public:
    virtual void addState(int id)=0;
    virtual void addInitState(int id)=0;
    virtual void addAccState(int id)=0;
    virtual void addInitAccState(int id)=0; 
    virtual void addState(int id, std::string name)=0;
    virtual void addInitState(int id, std::string name)=0;
    virtual void addAccState(int id, std::string name)=0;
    virtual void addInitAccState(int id, std::string name)=0;
    virtual void delState(int id)=0;
    virtual void addTransition(int fromId, Letter* l,  int toId)=0;
    virtual void delTransition(int fromId, Letter* l, int toId)=0;
    virtual Path* runOnWordOutPath(Word* word)=0;
    virtual bool runOnWordOutResult(Word* word)=0;
    virtual std::set<State*>& getStates()=0;
    virtual State* getInitState()=0;
    virtual std::set<State*>& getAccStates()=0;
    State* getState(int id);
    bool hasState(int id);
    bool hasTransition(int from, Letter* l, int to);
    void setName(std::string name);
    std::string getName();
    Alphabet* getAlphabet();
    void setAlphabet(Alphabet* alphabet);
    Automaton(/* args */);
    Automaton(Alphabet* alphabet);
    ~Automaton();
};

}


#endif
