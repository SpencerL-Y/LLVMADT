#include "../../include/checker/CheckerSampleBased.hpp"

namespace llvmadt{
CheckerSampleBased::CheckerSampleBased(PathChecker* pc, std::set<std::string> varNames)
{  
    this->pathChecker = pc;
    this->varNames = varNames;
}



CheckerSampleBased::~CheckerSampleBased()
{
    delete(this->pathChecker);
}
}