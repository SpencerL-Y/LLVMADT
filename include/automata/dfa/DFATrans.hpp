#ifndef DFAEdge_hpp
#define DFAEdge_hpp
#include "../abstract/Transition.hpp"


namespace llvmadt{
    template <class A>
    class DFATrans : public Transition<A>
    {
    private:
        /* data */
    public:
        DFATrans(/* args */);
        ~DFATrans();
    };
}

#endif