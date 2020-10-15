#ifndef CFAState_hpp
#define CFAState_hpp
#include <stdlib.h>
#include <vector>
#include <list>
#include <iostream>

namespace llvmadt{
class CFA;
class CFAEdge;
// State for CFA automaton
class CFAState
{
private:
    int id;
    std::list<CFAEdge*> edges;
    bool blockFinal; // true if is the final instruction of the basicblock

    //back pointer
    CFA* cfa;
    
public:
    CFAState(/* args */);
    ~CFAState();
    int getId();
    void setId(int id);
    std::string toString();
    void addEdge(CFAEdge* edge);
    std::list<CFAEdge*>& getEdges();
    bool isBlockFinal();
    void setBlockFinal(bool final);
    // go back to cfa
    CFA* getCfa();
};


}
#endif
