#include "../../include/checker/CheckerSampleBased.hpp"

namespace llvmadt{
CheckerSampleBased::CheckerSampleBased(PathSampler* ps, std::set<std::string> varNames)
{   
    this->pathSampler = ps;
    this->automaton = pathSampler->getAutomaton();
    this->varNames = varNames;
    this->pathChecker = new PathChecker();
    this->tlutil = new TLUtil();
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
            Path* p = this->pathSampler->samplePathEven(this->automaton->getInitState(), ctx);
            bool result = this->pathChecker->checkFinitePathProperty(p, spotLTLStr);
            if(result == false){
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

CheckerSampleBased::~CheckerSampleBased()
{
    delete(this->pathChecker);
    delete(this->tlutil);
}

}