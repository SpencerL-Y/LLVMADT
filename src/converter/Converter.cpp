#include "../../include/converter/Converter.hpp"
#include "../../include/converter/myTranslate.hpp"



namespace llvmadt{

std::list<CFA*> Converter::convertLLVM2CFAs(std::string ll_path)
{
    Translator T;

    Z3Test ts;
    ts.testFunction();
    llvm::LLVMContext context;
    llvm::SMDiagnostic err;
    std::unique_ptr<llvm::Module> Mod = parseIRFile(ll_path, err, context);

    if(!Mod)
    {
        std::cout << "Error: Module is null, please check" << std::endl;
    }
    int functionId = 0;
    std::list<CFA*> cfaList;

    for(llvm::Module::iterator m_iter = Mod->begin(); m_iter != Mod->end(); ++m_iter)
    {
        Translator::StoreMap MStr;
        Translator::BBMap BBID;

        z3::config cfg;
        cfg.set("auto_config", true);
        z3::context c(cfg);
        z3::solver s(c);

        CFA* currCFA = new CFA();
        llvm::Function* currFunc = &*m_iter;

        std::string name; 
        std::string funcID = std::to_string(functionId);
        std::string funcName = currFunc->getName();
        name = "Func_" + funcID + "_" + funcName;
        std::cout << "Function Name: " << name << '\n';
        currCFA->setName(name);
        int stateId = 0;
        
        //Add states
        for(llvm::Function::iterator f_iter = currFunc->begin(); f_iter != currFunc->end(); ++f_iter)
        {
            llvm::BasicBlock* bb = &*f_iter;
    
            // currCFA->addState(stateId);
            // std::cout << "add state " << stateId << std::endl;
            std::string bbName = bb->getName();
            std::cout << "block name: " << bbName << " block state id: " << stateId << '\n';
            BBID.insert(std::make_pair(bbName, std::to_string(stateId)));

            //TODO: more specific translation of instruction to the condition on the edge
            llvm::Instruction* lastInst;

            for(llvm::BasicBlock::iterator b_iter = bb->begin(); b_iter != bb->end(); ++b_iter){
                lastInst = &*b_iter;
                llvm::Instruction* currInst = &*b_iter;
                currCFA->addState(stateId);
                
                // z3::expr E = T.extractConstraints(currInst, &MStr, &c);
                // std::cout << "expr: " << E << '\n';

                //TODO: specify relation between state and instruction here
               
                //TODO: add state increasing logic here.
                stateId++;
            }
            // cfaList.push_front(currCFA);
        }
        currCFA->addState(stateId);

        llvm::errs() << "................get edges...................." << '\n';
        //Add edges
        int currID = 0;
        int brID = 0;
        for(llvm::Function::iterator f_iter = currFunc->begin(); f_iter != currFunc->end(); ++f_iter)
        {
            llvm::BasicBlock* bb = &*f_iter;
            std::string bbName = bb->getName();
            int bbID = std::stoi(BBID[bbName]);
            std::cout << "BB ID: " << bbID << '\n';

            llvm::errs() << "Basic Block name: " << bbName << '\n';
    
            for(llvm::BasicBlock::iterator b_iter = bb->begin(); b_iter != bb->end(); ++b_iter)
            {
                llvm::Instruction* currInst = &*b_iter;
                if (currInst != bb->getTerminator())
                {
                    z3::expr E = T.extractConstraints(currInst, &MStr, &c);
                    // std::cout << "expr: " << E << '\n';
                    currCFA->addEdge(currID, E, currID + 1);
                }
                else
                {
                    brID = currID;
                    // std::cout << "brID: " << brID << '\n';
                }
                currID++;
            }
            for(llvm::BasicBlock* succ : successors(bb) )
            {
                std::string nexName = succ->getName();
                int nexID = std::stoi(BBID[nexName]);

                // llvm::errs() << "Pred: " << Pred->getName() << "\n";
                z3::expr EBR = T.extractTBranch(bb, succ, &c);
                // std::cout << "brID: " << brID << '\n';
                // std::cout << "br expr: " << EBR << '\n'; 
                // std::cout << "nexID: " << nexID << '\n';
                currCFA->addEdge(brID, EBR, nexID);
            }
           
        }
        functionId ++;
        cfaList.push_front(currCFA);

        std::cout << "................CFA INFORMATION......................" << '\n';

        std::cout << "CFA name: " << currCFA->getName() << '\n';
        
        // std::list<CFAState*>::reverse_iterator it; 
        // std::list<CFAState*> States = currCFA->getStates();
        
        // for(it = States.rbegin(); it != States.rend(); it++)
        // {
        //     CFAState* currState = *it;

        //     int id = currState->getId();
        //     std::cout << id << '\n';
        // }
        std::list<CFAEdge*>::reverse_iterator it;
        std::list<CFAEdge*> Edges = currCFA->getEdges();
    
        for(it = Edges.rbegin(); it != Edges.rend(); it++)
        {
            CFAEdge* currEdge = *it;

            CFAState* fromState = currEdge->getFromState();
            CFAState* toState = currEdge->getToState();
            Guard* guard = currEdge->getGuard();

            int fId = fromState->getId();
            int toId = toState->getId();
            // std::string guardStr = guard->getGuardStr();
            // z3::expr E = c.bool_val(true);
            // guard->setGuard(&E);
            // guard->getGuardStr();

            std::cout << "from state: " << fId <<  " to state: " << toId << " guard: "  << '\n';
        }
    }
    return cfaList;
}
}