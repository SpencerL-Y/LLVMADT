#ifndef CFAState_hpp
#define CFAState_hpp
#include <stdlib.h>
#include <vector>
#include <list>
#include <iostream>
#include "./CFAEdge.hpp"
#include "./CFAInstruction.hpp"
#include "./CFA.hpp"

namespace llvmadt{
class CFAEdge;
class CFAInstruction;
class CFA;
class CFAState
{
private:
    int id;
    std::list<CFAEdge*> edges;
    CFAInstruction* instruction;
    bool blockFinal; // true if is the final instruction of the basicblock

    //back pointer
    CFA* cfa;
public:
    CFAState(/* args */);
    ~CFAState();
    int getId();
    void setId(int id);
    void setInstruction(CFAInstruction* instructions);
    CFAInstruction* getInstruction();
    std::string toString();
    void addEdge(int fromId, int toId);
    std::list<CFAEdge> getEdges();
    bool isBlockFinal();
    void setBlockFinal();

    // go back to cfa
    CFA* getCfa();

};

CFAState::CFAState(/* args */)
{
    this->instruction = new CFAInstruction();
}

CFAState::~CFAState()
{
    delete(this->instruction);
}
}
#endif
