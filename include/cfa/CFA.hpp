#ifndef CFA_hpp
#define CFA_hpp
#include <iostream>
#include <stdlib.h>
#include <vector>
#include <list>
#include <set>
#include <unistd.h>
#include "./CFAState.hpp"
#include "./CFAEdge.hpp"
#include <llvm/IR/Instruction.h>
namespace llvmadt{
// CFA is an intermediate automata data structure used for storing the information of IR CFGs

class CFA
{
private:
    // a state is a valuation of variables
    // startstate : indexed with 0
    std::set<CFAState*> states; 
    // edge can be regarded as change of valuation
    std::set<CFAEdge*> edges;
    std::set<std::string> VarNames;
    int stateNum;
    std::string name;
    
public:
    CFA(/* args */);
    ~CFA();
    std::set<CFAState*>& getStates();
    void setStates(std::set<CFAState*>& states);
    int getStateNum();
    void addState(int id, std::string bbName);
    void addState(CFAState* state);
    CFAState* getState(int id);
    void addEdge(int fromId, int toId);
    void addEdge(CFAState* fromState, llvm::Instruction* inst, CFAState* toState);
    void addEdge(int fromId, llvm::Instruction* inst, int toId);
    CFAEdge* getEdge(int fromId, int toId);
    std::set<CFAEdge*>& getEdges();
    void setName(std::string name);
    std::string getName();
    std::string toString();
    bool hasStateId(int id);
    bool hasEdgeId(int fromId, int toId);

    void setVarNames(std::set<std::string>& varNames);
    std::set<std::string> getVarNames();
};


}


#endif
