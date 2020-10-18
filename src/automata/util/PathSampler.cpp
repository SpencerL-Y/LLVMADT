#include "../../../include/automata/util/PathSampler.hpp"

namespace llvmadt{
    PathSampler::PathSampler(/* args */){
        this->automaton = nullptr;
    }

    PathSampler::PathSampler(Automaton* automaton){
        this->automaton = automaton;
    }
    
    PathSampler::~PathSampler(){

    }
    
    Automaton* PathSampler::getAutomaton(){
        return this->automaton;
    }

    int PathSampler::getSampleNum() 
    {
        return this->K;
    }

    void PathSampler::setSampleNum()
    {
        this->K = 4;
    }

    void PathSampler::setAutomaton(Automaton* automaton){;;
        this->automaton = automaton;
    }

    Path* PathSampler::samplePathEven(State* startState, z3::context* C){
        Path* path = new Path();
        // path->setAlphabet(startState->getAlphabet());
        PathSampler::VisitCount Count;
        Count[startState] = 0;
        this->id = 0;
        bool success = recursiveSort(startState, path, Count, C);
        if (success)
        {  
            
            Count.clear();
        }
        else
        {
            std::cout << "false sampling!" << '\n';
        }
        return path;
        
    }

    bool PathSampler::recursiveSort(State* currState, Path* path, VisitCount Count, z3::context* C)
    {
        srand(time(0));
        Count[currState] = Count[currState]  + 1;
        Translator T;
        std::set<Transition*> stateTransitions = currState->getStateTransitions();
        State* fromState; 
        State* toState;
        Letter* letter;

        int size = stateTransitions.size();
        succTrans succ;
        for (auto iter = stateTransitions.begin(); iter != stateTransitions.end(); ++iter) 
        {
            succ.push_back(*iter);
        }

        setSampleNum();
        std::cout << "..........recursive debug............" << '\n';
        std::cout << "K = " << getSampleNum() << '\n';
        std::cout << "currState count = " << Count[currState] << '\n';
        std::cout << "tran size: " << size << '\n';
        z3::expr* E;
        //path->setAlphabet(currState->getAlphabet());

        // resample currState less than K times
        if (Count[currState] < getSampleNum())
        {
            
            path->appendStemState(currState);

            if (size == 0)
            {
                return true;
            }
            else
            {
                this->id++;
                Transition* trans = succ[rand() % size];
                toState = trans->getToState();
                letter = trans->getLetter();
                
                llvm::Instruction* ins = ((LetterTypeInst*)letter->getContent())->getInstruction();
                
                if (!currState->getName().compare(toState->getName()))
                {
                    E = T.extractConstraints(ins, C);
                }
                else
                {
                    E = T.extractTBranch(ins, toState->getName(), C);
                }
        
                Letter* nl = new Letter();
                nl->setId(this->id);
                LetterTypeZ3Expr* z3content = new LetterTypeZ3Expr();
                z3content->setExpression(E, C);
                nl->setContent(z3content);
                path->appendStemLetter(letter);

                bool x = recursiveSort(toState, path, Count, C);
                return true;
            }
        }

        return true;
    }
}