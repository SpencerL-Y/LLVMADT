#include "../../../include/automata/util/PathSampler.hpp"

namespace llvmadt{
    template<class A>
    PathSampler<A>::PathSampler(/* args */){

    }

    template<class A>
    PathSampler<A>::PathSampler(Automaton<A>* automaton){
        this->automaton = automaton;
    }
    
    template<class A>
    PathSampler<A>::~PathSampler(){

    }
    
    template<class A>
    Automaton<A>* PathSampler<A>::getAutomaton(){
        return this->automaotn;
    }

    template<class A>
    void PathSampler<A>::setAutomaton(Automaton<A>* automaton){;;
        this->automaton = automaton;
    }

    template<class A>
    Path<A>* samplePathEven(State<A>* startState){
        Path<A> path;
    }
}