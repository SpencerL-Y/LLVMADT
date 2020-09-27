#include "../../../include/automata/dfa/DFA.hpp"
namespace llvmadt{

template <class A>
DFA<A>::DFA(){
    
}

template <class A>
DFA<A>::~DFA(){

}


template <class A>
void DFA<A>::addState(int id){
    for(State<A>* state : this->states){
        if(state->getId() == id){
            std::cout << "add state error, state already exists" << std::endl;
            return;
        }
    }
    State<A>* ns = new DFAState<A>();
    ns->setId(id);
    ns->setAlphabet(this->getAlphabet);
    this->states.push_back(ns);
}


template <class A>
void DFA<A>::addInitState(int id){
    if(this->getInitState() != nullptr){
        std::cout << "add init state error, only one init state allowed" << std::endl;
        return;
    }
    for(State<A>* state : this->states){
        if(state->getId() == id){
            std::cout << "add init state error, state already exists" << std::endl;
            return;
        }
    }
    
    State<A>* ns = new DFAState<A>();
    ns->setId(id);
    ns->setAlphabet(this->getAlphabet);
    ns->setInit();
    this->states.push_back(ns);
    this->initState = ns;
}

template <class A>
void DFA<A>::addAccState(int id){
    for(State<A>* state : this->states){
        if(state->getId() == id){
            std::cout << "add init state error, state already exists" << std::endl;
            return;
        }
    }
    
    State<A>* ns = new DFAState<A>();
    ns->setId(id);
    ns->setAlphabet(this->getAlphabet);
    ns->setAcc();
    this->states.push_back(ns);
    this->accStates.push_back(ns);
}

template <class A>
void DFA<A>::delState(int id){
    if(!this->hasState(id)){
        std::cout << "del state error, state not exists" << std::endl;
        return;
    }
    int stateId = 0;
    State<A>* temp;
    for(State<A>* state : this->getStates()){
        if(state->getId() == id){
            temp = state;
            this->states.erase(stateId);
            break;
        }
        stateId++;
    }
    if(temp->isAccState()){
        int accId = 0;
        for(State<A>* s : this->accStates){
            if(s->getId() == id){
                this->accStates.erase(accId);
                break;
            }
            accId++;
        }
    }
    if(temp->isInitialState()){
        this->initState = nullptr;
    }
    delete(temp);
}



template <class A>
void DFA<A>::addTransition(int fromId, Letter<A>* l, int toId){
    if(l->getAlphabet() != this->alphabet){
        std::cout << "add transition error, inconsistent alphabet" << std::endl;
        return;
    }
    if(this->hasTransition(fromId, l, toId)){
        std::cout << "add transition error, transition exists" << std::endl;
        return;
    }
    DFATrans<A>* dfat = new DFATrans<A>(fromId, l, toId);
    this->transitions.push_back(dfat);
    this->getState(fromId)->addTransition(dfat);
}

template <class A>
void DFA<A>::delTransition(int fromId, Letter<A>* l, int toId){
    if(!this->hasTransition(fromId, l, toId)){
        std::cout << "del transition error, transition not exists" << std::endl;
        return;
    }
    Transition<A>* tranTemp;
    int tranId = 0;
    for(Transition<A>* tran : this->transitions){
        if(tran->getFromState()->getId() == fromId &&
           tran->getToState()->getId() == toId &&
           tran->getLetter()->getId() == l->getId()){
               tranTemp = tran;
               this->transitions.erase(tranId);
               break;
           }
        tranId++;
    }


}


template <class A>
Path<A>* DFA<A>::runOnWordOutPath(Word<A>* word){
    if(word->getAlphabet() != this->alphabet){
        std::cout << "run on word error, alphabet not consistent" << std::endl;
        return nullptr;
    }
    Path<A>* path = new Path(word);
    DFAState<A>* currentState = this->initState;
    DFAState<A>* temp = currentState;
    path->appendStemState(temp);
    for(Letter<A>* l : word->getWordStem()){
        currentState = this->executeLetter(currentState, l);
        DFAState<A>* tempState = currentState;
        path->appendStemState(tempState);
    }
    return path;
}

template <class A>
bool DFA<A>::runOnWordOutResult(Word<A>* word){
    if(word->getAlphabet() != this->alphabet){
        std::cout << "run on word error, alphabet not consistent" << std::endl;
        return nullptr;
    }
    DFAState<A>* currentState = this->initState;
    for(Letter<A>* l : word->getWordStem()){
        currentState = this->executeLetter(currentState, l);
    }
    if(currentState->isAccState()){
        return true;
    } else {
        return false;
    }
}

template <class A>
DFAState<A>* DFA<A>::executeLetter(DFAState<A>* currentState, Letter<A>* l){
    return currentState->executeLetter(l);
}


}