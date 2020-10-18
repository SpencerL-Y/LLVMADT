#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include "../include/cfa/CFA.hpp"
#include "../include/converter/Converter.hpp"
#include "../include/automata/util/PathSampler.hpp"
#include "../include/checker/PathChecker.hpp"

using namespace llvmadt;


int main(int argc, char** argv){
    srand(time(0));
    llvm::LLVMContext context;
    llvm::SMDiagnostic err;
    std::string ll_path = argv[1];
    std::unique_ptr<llvm::Module> Mod = parseIRFile(ll_path, err, context);
    llvm::Module*  mod  = Mod.get();

    z3::context c;
    Converter* converter = new Converter();
    std::list<CFA*> cfalist = converter->convertLLVM2CFAs(mod);
    CFA *cfa = cfalist.front();
    std::set<CFAEdge*>::iterator it;
    std::set<CFAEdge*> Edges = cfa->getEdges();

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

    std::cout << "name: " << cfa->getName() << '\n';

    Automaton* dfa = converter->convertCFA2DFA(cfa);

    std::cout << "dfa name: " << dfa->getName() << '\n';
    // std::cout << "init state id: " << dfa->getInitState()->getId() << '\n';

    PathSampler sampler;
    Path* path = sampler.samplePathEven(dfa->getInitState(), &c);

    std::cout << ".............path................." << '\n';
    std::vector<State*>::iterator itit;
    std::vector<State*> states = path->getStemStates();

    int letterI = 0;
  
    for (State* currState : path->getStemStates() )
    {
        std::cout << "states: " << currState->getId() << '\n';
        Letter* letter =  path->getStemLetter(letterI);
        std::cout << "z3:expr: " <<((LetterTypeZ3Expr*) letter->getContent())->getExpression()->to_string() << std::endl;
        letterI++;

    }
    std::cout << "...............Path checker............" << std::endl;
    PathChecker pc;
    z3::solver* s = pc.checkFinitePathFeasibility(path);
    if(s == nullptr){
        std::cout << "not satisfied" << std::endl;
    } else {
        std::cout << "satisfied" << std::endl;
        std::cout << s->get_model() << std::endl;
        delete(s);
    }

    std::cout << "..............Samplebased Checker............" << std::endl;


    // CFA cfa;
    // cfa.addState(1);
    // cfa.addState(2);
    // cfa.addEdge(1,2);
    delete(converter);
    delete(path);
    return 0;
}