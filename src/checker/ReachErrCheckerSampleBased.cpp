#include "../../include/checker/ReachErrCheckerSampleBased.hpp"
#include "./CheckerUtil.cpp"


namespace llvmadt
{
    ReachErrCheckerSampleBased::ReachErrCheckerSampleBased(/* args */)
    {
    }
    
    ReachErrCheckerSampleBased::~ReachErrCheckerSampleBased()
    {
    }

    Path* ReachErrCheckerSampleBased::checkReachError(std::string yamlPath, int sampleNum){
        this->svParser.parseSVCompYamlFile(yamlPath);
        srand(time(NULL));
        llvm::LLVMContext context;
        llvm::SMDiagnostic err;
        std::string inputFilePath = this->svParser.getInputFiles();
        std::string llPath = generateLLVMFile(inputFilePath);
        std::unique_ptr<llvm::Module> Mod = parseIRFile(llPath, err, context);
        llvm::Module*  mod  = Mod.get();

        z3::context c;
        Converter* converter = new Converter();
        std::list<CFA*> cfalist = converter->convertLLVM2CFAs(mod);
        CFA *cfa = cfalist.back();

        Automaton* dfa = converter->convertCFA2DFA(cfa);
        std::cout << ".............path................." << '\n';

        this->pathSampler = new PathSampler(dfa);
        this->pathSampler->setAutomaton(dfa);
        int i = 0;
        std::string verdict = this->svParser.extractReachErrorResult();
        while(i < sampleNum){
            Path* path = this->pathSampler->samplePathEven(dfa->getInitState(), &c);
            if(path->isReachError()){
                bool result = this->pathChecker->checkFinitePathFeasibility(path);
                if(result == true){
                    if(!verdict.compare("true")){
                        std::cout << "REACH_ERROR CHECKING ERROR" << std::endl;
                    }
                    return path;
                }
                i++;
            }
        }
        return nullptr;
    }
} // namespace llvmadt
