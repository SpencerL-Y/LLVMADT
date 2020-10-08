#include "../../../include/automata/util/PathSampler.hpp"

namespace llvmadt{
    
    PathSampler::PathSampler(/* args */){

    }

    
    PathSampler::PathSampler(Automaton* automaton){
        this->automaton = automaton;
    }
    
    
    PathSampler::~PathSampler(){

    }
    
    
    Automaton* PathSampler::getAutomaton(){
        return this->automaton;
    }

    
    void PathSampler::setAutomaton(Automaton* automaton){;;
        this->automaton = automaton;
    }

    
    Path* samplePathEven(State* startState){
        Path path;
    }
}