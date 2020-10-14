#include "../../include/converter/Converter.hpp"
#include "../../include/converter/myTranslate.hpp"



namespace llvmadt{

std::list<CFA*> Converter::convertLLVM2CFAs(std::string ll_path, z3::context *c)
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
        Translator::BBMap BBID;
        // z3::config cfg;
        // cfg.set("auto_config", true);
        // z3::context c(cfg);
        // z3::solver s(c);

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
                    // z3::expr* E = new z3::expr(c);
                    // E = T.extractConstraints(currInst, &MStr, &c);
                    z3::expr* E = T.extractConstraints(currInst, c);
                    // *E = c.bool(true);
                    // std::cout << "id: " << currID << '\n';
                    // std::cout << "expr: " << *E << '\n';
                    int nexID = currID + 1;
                    currCFA->addEdge(currID, E,  nexID);
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
                // z3::expr* EBR = new z3::expr(c);
                // EBR = T.extractTBranch(bb, succ, &c);
                z3::expr* EBR = T.extractTBranch(bb, succ, c);
                // std::cout << "brID: " << brID << '\n';
                // std::cout << "br expr: " << *EBR << '\n'; 
                // std::cout << "nexID: " << nexID << '\n';
                currCFA->addEdge(brID, EBR, nexID);
            }
           
        }
        std::set<std::string> varNames = T.getVar();
        currCFA->setVarNames(varNames);

        std::cout << "..................varIndex..................." << '\n';
        std::map<std::string, int>* v = new std::map<std::string, int>;
        *v = T.getIndex();
        std::map<std::string, int>::iterator i;
        for(i = v->begin(); i != v->end(); ++i)
        {
            std::cout << "var: " << (*i).first << " k:" << (*i).second << '\n';
        }

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
            std::string guardStr = guard->getGuardStr();
            // z3::expr E = c.bool_val(true);
            // guard->setGuard(&E);
            // guard->getGuardStr();

            std::cout << "from state: " << fId <<  " to state: " << toId << " guard: " << guardStr << '\n';
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

    Alphabet* z3ExprAlphabet = new Alphabet();

    Automaton* resultDFA = new DFA();
    resultDFA->setAlphabet(z3ExprAlphabet);
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
        Letter* l = z3ExprAlphabet->getLetter(edge->getGuard()->toString());
        if(l == nullptr){
        std::cout << edge->getGuard()->getExpr()->to_string()<< std::endl;
            LetterTypeZ3Expr* z3l = new LetterTypeZ3Expr(edge->getGuard()->getExpr(), cfa->getContext());
            
            z3ExprAlphabet->addLetter(z3l);
            //std::cout << edge->getGuard()->toString() << std::endl;
            l = z3ExprAlphabet->getLetter(edge->getGuard()->toString());
            l->setAlphabet(z3ExprAlphabet);
        } else {
            l->setAlphabet(z3ExprAlphabet);
        }
        resultDFA->addTransition(edge->getFromState()->getId(), l, edge->getToState()->getId());
        
        // std::cout << "here00" << std::endl;
    }

    resultDFA->setName(cfa->getName());
    return resultDFA;
}


Automaton* Converter::convertLTL2BA(std::string ltl){
}

}