#ifndef DFAEdge_hpp
#define DFAEdge_hpp
#include "../abstract/Transition.hpp"


namespace llvmadt{
    class DFATrans : public Transition
    {
    private:
        /* data */
    public:
        DFATrans(/* args */);
        ~DFATrans();
    };
}

#endif