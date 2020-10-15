#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/cfa/CFA.hpp"
#include "../include/converter/Converter.hpp"
#include "../include/automata/util/PathSampler.hpp"

using namespace llvmadt;
int main(int argc, char** argv){
    z3::context c;
    Converter converter;
    std::list<CFA*> cfalist = converter.convertLLVM2CFAs(argv[1]);
    CFA *cfa = cfalist.front();
    // std::set<CFAEdge*>::reverse_iterator it;
    // std::set<CFAEdge*> Edges = cfa->getEdges();

    std::cout << "......................main..........................." << '\n';
    std::cout << '\n';

    std::cout << "...................var test begin................." << '\n';
    std::set<std::string> VarNames = cfa->getVarNames();
    std::set<std::string>::iterator i;
  
    for (i = VarNames.begin(); i != VarNames.end(); i++)
    {
        std::string currVar = *i;
        std::cout << "Var: " << currVar << '\n';
    }

    std::cout << "...................var test end................." << '\n';


    // for(it = Edges.rbegin(); it != Edges.rend(); it++)
    // {
    //     CFAEdge* currEdge = *it;

    //     CFAState* fromState = currEdge->getFromState();
    //     CFAState* toState = currEdge->getToState();
    //     Guard* guard = currEdge->getGuard();

    //     int fId = fromState->getId();
    //     int toId = toState->getId();
    //     std::string guardStr = guard->getGuardStr();
    //     // z3::expr E = c.bool_val(true);
    //     // guard->setGuard(&E);
    //     // guard->getGuardStr();
       
    //     std::cout << "from state: " << fId <<  " to state: " << toId << " guard: " << guardStr << '\n';
    // } 
    // std::cout << "name: " << cfa->getName() << '\n';

    // Automaton* dfa = converter.convertCFA2DFA(cfa);

    // std::cout << "dfa name: " << dfa->getName() << '\n';
    // std::cout << "init state id: " << dfa->getInitState()->getId() << '\n';

    // PathSampler sampler;
    // Path* path = sampler.samplePathEven(dfa->getInitState());

    // std::cout << ".............path................." << '\n';
    // std::vector<State*>::iterator it;
    // std::vector<State*> states = path->getStemStates();
  
    // for (it = states.begin(); it != states.end(); it++)
    // {
    //     State* currState = *it;
    //     std::cout << "states: " << currState->getId() << '\n';
    // }

    // CFA cfa;
    // cfa.addState(1);
    // cfa.addState(2);
    // cfa.addEdge(1,2);
    return 0;
}