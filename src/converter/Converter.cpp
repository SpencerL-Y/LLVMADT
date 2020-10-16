#include "../../include/converter/Converter.hpp"
#include "../../include/converter/myTranslate.hpp"



namespace llvmadt{

std::list<CFA*> Converter::convertLLVM2CFAs(llvm::Module* mod)
{
    Translator T;

//     llvm::LLVMContext context;
//     llvm::SMDiagnostic err;
//     // std::unique_ptr<llvm::Module> Mod = parseIRFile(ll_path, err, context);
//    llvm::Module* module = parseIRFile(ll_path, err, context);
   // this->readIRFile(ll_path);
    if(!mod)
    {
        std::cout << "Error: Module is null, please check" << std::endl;
    }
    int functionId = 0;
    std::list<CFA*> cfaList;

    for(llvm::Module::iterator m_iter =  mod->begin(); m_iter !=  mod->end(); ++m_iter)
    {
        Translator::BBMap BBID;

        CFA* currCFA = new CFA();
        llvm::Function* currFunc = &*m_iter;

        std::string name; 
        std::string funcID = std::to_string(functionId);
        std::string funcName = currFunc->getName();
        name = "Func_" + funcID + "_" + funcName;
        std::cout << "Function Name: " << name << '\n';
        currCFA->setName(name);
        int stateId = 0;
        
        // Add states
        for(llvm::Function::iterator f_iter = currFunc->begin(); f_iter != currFunc->end(); ++f_iter)
        {
            llvm::BasicBlock* bb = &*f_iter;
    
            // currCFA->addState(stateId);
            // std::cout << "add state " << stateId << std::endl;
            std::string bbName = bb->getName();
            std::cout << "block name: " << bbName << " block state id: " << stateId << '\n';
            BBID.insert(std::make_pair(bbName, std::to_string(stateId)));

            for(llvm::BasicBlock::iterator b_iter = bb->begin(); b_iter != bb->end(); ++b_iter){
                std::cout << "add state id: " << stateId << '\n';
                currCFA->addState(stateId, bb->getName());
                stateId++;
            }
        }
        // cfaList.push_front(currCFA);

        llvm::errs() << "................get edges...................." << '\n';

        // Add edges
        int currID = 0;
        int brID = 0;
        for(llvm::Function::iterator f_iter = currFunc->begin(); f_iter != currFunc->end(); ++f_iter)
        {
            llvm::BasicBlock* bb = &*f_iter;
            std::string bbName = bb->getName();
            int bbID = std::stoi(BBID[bbName]);
            // std::cout << "BB ID: " << bbID << '\n';
            // llvm::errs() << "Basic Block name: " << bbName << '\n';
    
            for(llvm::BasicBlock::iterator b_iter = bb->begin(); b_iter != bb->end(); ++b_iter)
            {
                llvm::Instruction* currInst = &*b_iter;
                T.extractVarName(currInst);

                if (currInst != bb->getTerminator())
                {
                    int nextID = currID + 1;
                    currCFA->addEdge(currID, currInst, nextID);

                    llvm::errs() << "from ID: " << currID << " inst: " << *currInst << " to ID: " << nextID << '\n';
                }
                else
                {
                    brID = currID;
                    for(llvm::BasicBlock* succ : successors(bb))
                    {
                        std::string nexName = succ->getName();
                        int nexID = std::stoi(BBID[nexName]);
                        currCFA->addEdge(brID, currInst, nexID);
                        llvm::errs() << "from ID: " << brID << " inst: " << *currInst << " to ID: " << nexID << '\n';
                    }
                }
                currID++;
            }
            
        }
        
        std::set<std::string> varNames = T.getVar();
        currCFA->setVarNames(varNames);

        // std::cout << "..................varIndex..................." << '\n';
        // std::map<std::string, int>* v = new std::map<std::string, int>;
        // *v = T.getIndex();
        // std::map<std::string, int>::iterator i;
        // for(i = v->begin(); i != v->end(); ++i)
        // {
        //     std::cout << "var: " << (*i).first << " k:" << (*i).second << '\n';
        // }

        functionId ++;
        cfaList.push_back(currCFA);

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
        std::set<CFAEdge*>::iterator it;
        std::set<CFAEdge*> Edges = currCFA->getEdges();
    
        for(it = Edges.begin(); it != Edges.end(); it++)
        {
            CFAEdge* currEdge = *it;

            CFAState* fromState = currEdge->getFromState();
            CFAState* toState = currEdge->getToState();
            Guard* guard = currEdge->getGuard();

            int fId = fromState->getId();
            int toId = toState->getId();
            llvm::Instruction* guardStr = guard->getInstruction();

            // z3::expr E = c.bool_val(true);
            // guard->setGuard(&E);
            // guard->getGuardStr();

            llvm::errs()  << "from state: " << fId <<  " to state: " << toId << " guard: " << *guardStr << '\n';
        }
    }
    return cfaList;
}

Automaton* Converter::convertLTLf2DFA(std::string ltlfStr){
    spot::parsed_formula pf = spot::parse_infix_psl(ltlfStr);
    if(pf.format_errors(std::cerr)){
        return nullptr;
    }
    spot::twa_graph_ptr aut = spot::ltl_to_tgba_fm(pf.f, spot::make_bdd_dict());
}


Automaton* Converter::convertCFA2DFA(CFA* cfa){

    Alphabet* instAlphabet = new Alphabet();

    Automaton* resultDFA = new DFA();
    resultDFA->setAlphabet(instAlphabet);
    std::set<llvmadt::CFAState*>::iterator it;
    for(it=cfa->getStates().begin(); it!=cfa->getStates().end(); it++){
        CFAState* cs = *it;
        // all states of the program are accepting
        if(cs->getId() == 0){
            resultDFA->addInitAccState(cs->getId());
        } else {
            resultDFA->addAccState(cs->getId());
        }
        std::cout << "add state " + std::to_string(cs->getId()) << std::endl;
    }

    std::set<CFAEdge*>::iterator it2;
    for(it2 = cfa->getEdges().begin(); it2 != cfa->getEdges().end(); ++it2){
        CFAEdge* edge = *it2;
        Letter* l = new Letter();
        LetterTypeInst* il = new LetterTypeInst(edge->getGuard()->getInstruction());
        l->setId(instAlphabet->getLettersSize());
        l->setContent(il);
        l->setAlphabet(instAlphabet);
        instAlphabet->addLetter(il);
        resultDFA->addTransition(edge->getFromState()->getId(), l, edge->getToState()->getId());
        
        // std::cout << "here00" << std::endl;
    }

    resultDFA->setName(cfa->getName());
    return resultDFA;
}


Automaton* Converter::convertLTL2BA(std::string ltl){
}

}