#ifndef DFAEdge_hpp
#define DFAEdge_hpp
#include "../abstract/Transition.hpp"


namespace llvmadt{
    template <class T>
    class DFAState;
    template <class A>
    class DFATrans : public Transition<A>
    {
    private:
        /* data */
    public:
        DFATrans(/* args */);
        DFATrans(Alphabet<A>* alphabet);
        DFATrans(DFAState<A>* from, Letter<A>* l, DFAState<A>* to);
        ~DFATrans();
        
    };
}

#endif