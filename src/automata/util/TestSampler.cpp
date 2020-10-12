#include "../../../include/automata/util/TestSampler.hpp"

namespace llvmadt{
    TestSampler::TestSampler(/* args */){

    }

    TestSampler::TestSampler(Automaton* automaton){
        this->automaton = automaton;
    }
    
    TestSampler::~TestSampler(){

    }
    
    Automaton* TestSampler::getAutomaton(){
        return this->automaton;
    }

    int TestSampler::getSampleNum() 
    {
        return this->K;
    }

    void TestSampler::setAutomaton(Automaton* automaton){;;
        this->automaton = automaton;
    }

    Path* TestSampler::samplePathEven(State* startState){
        Path path;
        TestSampler::VisitCount Count;
        Count[startState] = 0;

        bool success = recursiveSort(startState, &path, Count);
        if (success)
        {  
            
            Count.clear();
        }
        else
        {
            std::cout << "false sampling!" << '\n';
        }
        return &path;
        
    }

    bool TestSampler::recursiveSort(State* currState, Path* path, VisitCount Count)
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
                path->appendStemLetter(letter);

                bool x = recursiveSort(toState, path, Count);
                return true;
            }
        }

        return true;
    }
}