#ifndef DFA_hpp
#define DFA_hpp
#include "../abstract/Automaton.hpp"
#include "../dfa/DFAState.hpp"
#include "../dfa/DFATrans.hpp"

namespace llvmadt{
template<class A>
class DFA : public Automaton<A>
{
private:
    virtual void addState(int id);
    virtual void addInitState(int id);
    virtual void addAccState(int id);
    virtual void delState(int id);
    virtual void addTransition(int fromId, Letter<A>* l,  int toId);
    virtual void delTransition(int fromId, Letter<A>* l, int toId);
    virtual Path<A>* runOnWord(Word<A>* word);
    virtual State<A>* getInitState();
    virtual std::list<State<A>*> getAccStates();
public:
    DFA(/* args */);
    ~DFA();
};
}

#endif