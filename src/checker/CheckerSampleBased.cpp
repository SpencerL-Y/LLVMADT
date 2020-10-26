#include "../../include/checker/CheckerSampleBased.hpp"

namespace llvmadt{
CheckerSampleBased::CheckerSampleBased(PathSampler* ps, std::set<std::string> varNames, z3::context* c)
{   
    this->pathSampler = ps;
    this->automaton = pathSampler->getAutomaton();
    this->varNames = varNames;
    this->tlutil = new TLUtil(c);
    this->pathChecker = new PathChecker(this->tlutil, c);
}


PathChecker* CheckerSampleBased::getPathChecker(){
    return this->pathChecker;
}


Automaton* CheckerSampleBased::getAutomaton(){
    return this->automaton;
}

void CheckerSampleBased::setAutomaton(Automaton* automaton){
    if(this->automaton == nullptr){
        this->automaton = automaton;
    }
}

std::set<std::string>& CheckerSampleBased::getVarNames(){
    return this->varNames;
}

Path* CheckerSampleBased::checkProperty(std::string spotLTLStr, int pathNum, z3::context* ctx){
    
    spot::parsed_formula pf = spot::parse_infix_psl(spotLTLStr);
    spot::formula f = pf.f;
    if(this->tlutil->isSimpleLTL(f)){
        for(int i = 0; i < pathNum; i++){

            std::cout << "check path property" << std::endl;
            Path* p = this->pathSampler->samplePathEven(this->automaton->getInitState(), ctx);
            std::cout << "path sampler end" << std::endl;
            bool result = this->pathChecker->checkFinitePathProperty(p, spotLTLStr, this->varNames);
            if(result == false){
                std::cout << "false" << std::endl;
                return p;
            }
            delete(p);
        }
    } else {
        std::cout << "The formula is too complex currently, to be added later" << std::endl;
        return nullptr;
    }
    return nullptr;
}

TLUtil* CheckerSampleBased::getTlUtil(){
    return this->tlutil;
}


void CheckerSampleBased::addBind(std::string ltlAp, z3::expr* expr){
    this->tlutil->addApZ3ExprMap(ltlAp, expr);
}

CheckerSampleBased::~CheckerSampleBased()
{
    delete(this->pathChecker);
    delete(this->tlutil);
}

}