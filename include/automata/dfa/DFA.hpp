#ifndef DFA_hpp
#define DFA_hpp
#include "../abstract/Automaton.hpp"
#include "../dfa/DFAState.hpp"
#include "../dfa/DFATrans.hpp"

namespace llvmadt{

class DFA : public Automaton
{
private:
public:
    void addState(int id);
    void addInitState(int id);
    void addAccState(int id);
    void addInitAccState(int id);
    void addState(int id, std::string name);
    void addInitState(int id, std::string name);
    void addAccState(int id, std::string name);
    void addInitAccState(int id, std::string name);
    void delState(int id);
    void addTransition(int fromId, Letter* l,  int toId);
    void delTransition(int fromId, Letter* l, int toId);
    Path* runOnWordOutPath(Word* word);
    bool runOnWordOutResult(Word* word);
    std::set<State*>& getStates();
    State* getInitState();
    std::set<State*>& getAccStates();

    DFAState* executeLetter(DFAState* currentState, Letter* l);

    DFA(/* args */);
    ~DFA();
};
}

#endif
