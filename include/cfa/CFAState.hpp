#ifndef CFAState_hpp
#define CFAState_hpp
#include <stdlib.h>
#include <vector>
#include <list>
#include <iostream>
#include "./CFAInstruction.hpp"

namespace llvmadt{
class CFA;
class CFAEdge;
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
    void addEdge(CFAEdge* edge);
    std::list<CFAEdge*> getEdges();
    bool isBlockFinal();
    void setBlockFinal(bool final);

    // go back to cfa
    CFA* getCfa();

};


}
#endif
