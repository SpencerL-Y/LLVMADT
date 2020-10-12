#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/cfa/CFA.hpp"
#include "../include/converter/Converter.hpp"
using namespace llvmadt;
int main(int argc, char** argv){
    Converter converter;
    std::list<CFA*> cfalist = converter.convertLLVM2CFAs(argv[1]);

    CFA *cfa = cfalist.front();
    // std::cout << "name: " << cfa->getName() << '\n';

    Automaton* dfa = converter.convertCFA2DFA(cfa);
    std::cout << "init state id: " << dfa->getInitState()->getId() << '\n';
    

    // CFA cfa;
    // cfa.addState(1);
    // cfa.addState(2);
    // cfa.addEdge(1,2);
    return 0;
}