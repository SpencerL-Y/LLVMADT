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

    Path* PathSampler::samplePathEven(State* startState){
        Path* path = new Path();
        path->setAlphabet(startState->getAlphabet());
        PathSampler::VisitCount Count;
        Count[startState] = 0;

        bool success = recursiveSort(startState, path, Count);
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

    bool PathSampler::recursiveSort(State* currState, Path* path, VisitCount Count)
    {
        srand(time(0));
        Count[currState] = Count[currState]  + 1;
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
        std::cout << "K = " << getSampleNum() << '\n';
        std::cout << "currState count = " << Count[currState] << '\n';
        std::cout << "tran size: " << size << '\n';
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
                Transition* trans = succ[rand() % size];
                toState = trans->getToState();
                letter = trans->getLetter();
                std::cout << ((LetterTypeZ3Expr*)letter->getContent())->getExpression()->to_string() << std::endl;
                path->appendStemLetter(letter);

                bool x = recursiveSort(toState, path, Count);
                return true;
            }
        }

        return true;
    }
}