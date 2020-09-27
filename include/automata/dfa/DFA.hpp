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
    void addState(int id);
    void addInitState(int id);
    void addAccState(int id);
    void delState(int id);
    void addTransition(int fromId, Letter<A>* l,  int toId);
    void delTransition(int fromId, Letter<A>* l, int toId);
    Path<A>* runOnWordOutPath(Word<A>* word);
    bool runOnWordOutResult(Word<A>* word);
    State<A>* getInitState();
    std::list<State<A>*> getAccStates();

    DFAState<A>* executeLetter(DFAState<A>* currentState, Letter<A>* l);

public:
    DFA(/* args */);
    ~DFA();
};
}

#endif
