#include "../../../include/automata/dfa/DFA.hpp"
namespace llvmadt{

template <class A>
DFA<A>::DFA(){
    
}

template <class A>
DFA<A>::~DFA(){

}


template <class A>
void DFA<A>::addState(int id){
    State<A>* ns = new DFAState<A>();
    ns->setId(id);
    
}


}