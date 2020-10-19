#include <cstdlib>
#include <stdio.h>
#include <iostream>
#include <ctime>
#include <map>
#include <utility>
#include "../include/cfa/CFA.hpp"
#include "../include/converter/Converter.hpp"
#include "../include/automata/util/PathSampler.hpp"
#include "../include/checker/PathChecker.hpp"
#include "../include/checker/CheckerSampleBased.hpp"

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

    std::cout << ".............path................." << '\n';

    PathSampler sampler;
    Path* path = sampler.samplePathEven(dfa->getInitState(), &c);
    // std::cout << "x index: " << path->getVarIndexVarName("x") << '\n';
    // std::cout << "ddd" << '\n';
    // std::vector<State*>::iterator itit;
    std::vector<State*> states = path->getStemStates();

    int letterI = 0;
    int length = 0;
    for (State* currState : path->getStemStates() )
    {
        std::cout << "states: " << currState->getId() << '\n';
        if (path->getCurrentVarIndex(length).find("y") == path->getCurrentVarIndex(length).end())
        {
            std::cout << "kkk" << '\n';
        }
        else
        {
            std::cout << "curr index: " <<  path->getCurrentVarIndex(length).find("y")->second << '\n'; 
        }
        
        Letter* letter =  path->getStemLetter(letterI);
        std::cout << "z3:expr: " <<((LetterTypeZ3Expr*) letter->getContent())->getExpression()->to_string() << std::endl;
        letterI++;
        length++;

    }
    std::cout << "...............Path checker............" << std::endl;
    PathChecker pc(&c);
    z3::solver* s = pc.checkFinitePathFeasibility(path);
    if(s == nullptr){
        std::cout << "not satisfied" << std::endl;
    } else {
        std::cout << "satisfied" << std::endl;
        std::cout << s->get_model() << std::endl;
        delete(s);
    }
    z3::expr apap1 = (c.int_const("x") > 0);

    pc.addTLUtilApStrMap("a", &apap1);

    pc.checkFinitePathProperty(path, "Fa");

    // std::cout << "..............Samplebased Checker............" << std::endl;

    // std::map<std::string, int> mapmap;
    // std::string s1 = "str";
    // std::string s2 = "str";
    // mapmap.insert(std::make_pair(s2, 1));
    // if(mapmap.find(s2) == mapmap.end()){
    //     std::cout << "false" << std::endl;
    // }
    // CFA cfa;
    // cfa.addState(1);
    // cfa.addState(2);
    // cfa.addEdge(1,2);



    std::cout << "...............TLUtil.................." << std::endl;
    TLUtil* ut = new TLUtil(&c);
    z3::expr xe = c.int_const("x");
    z3::expr ap1 = (xe > 0);
    z3::expr ap2 = (xe == 1);
    ut->addApZ3ExprMap("a", &ap1);
    ut->addApZ3ExprMap("b", &ap2);
    spot::parsed_formula pf = spot::parse_infix_psl("Fa");
    spot::formula& f = pf.f;
    z3::expr* expr = ut->extractSimpleFormula_G(f);
    //std::cout << "expr: " << expr->to_string() << std::endl;
    std::cout << ut->isSimpleLTL(f) << std::endl;
    std::cout << "origin: " << ap1.to_string() << std::endl;
    z3::expr_vector vec1(c);
    vec1.push_back(c.int_const("x1"));
    z3::expr_vector vec2(c);
    vec2.push_back(xe);
    z3::expr ap3 = ap1.substitute(vec2, vec1);

    std::cout << "subs: " << ap3.to_string() << std::endl;


    std::cout << ".....................map test............." << std::endl;
    std::map<std::string, int> strIntMap;
    std::map<std::string, int> strIntMap2;
    strIntMap2["a"] = 0;
    if(strIntMap.find("ddd") == strIntMap.end()){
        std::cout << "wtf" << std::endl;
    }
    std::cout << "dkdkd: " << strIntMap.find("ddd")->second << std::endl;
    
    std::cout << "................sampleBasedChecker............" << std::endl;
    
    
    
    delete(ut);
    delete(converter);
    delete(path);
    return 0;
}