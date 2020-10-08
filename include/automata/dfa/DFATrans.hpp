#ifndef DFAEdge_hpp
#define DFAEdge_hpp
#include "../abstract/Transition.hpp"


namespace llvmadt{
    class DFAState;
    
    class DFATrans : public Transition
    {
    private:
        /* data */
    public:
        DFATrans(/* args */);
        DFATrans(Alphabet* alphabet);
        DFATrans(State* from, Letter* l, State* to);
        DFATrans(int fromId, Letter* l, int toId);
        ~DFATrans();
        
    };
}

#endif