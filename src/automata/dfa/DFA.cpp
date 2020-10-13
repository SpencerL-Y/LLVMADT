#include "../../../include/automata/dfa/DFA.hpp"
namespace llvmadt{


DFA::DFA(){
    
}


DFA::~DFA(){

}



void DFA::addState(int id){
    for(State* state : this->states){
        if(state->getId() == id){
            std::cout << "add state error, state already exists" << std::endl;
            return;
        }
    }
    State* ns = new DFAState();
    ns->setId(id);
    if(this->getAlphabet() == nullptr){
        ns->setAlphabet(this->getAlphabet());
    }
    this->states.insert(ns);
}



void DFA::addInitState(int id){
    if(this->getInitState() == nullptr){
        std::cout << "add init state error, only one init state allowed" << std::endl;
        return;
    }
    for(State* state : this->states){
        if(state->getId() == id){
            std::cout << "add init state error, state already exists" << std::endl;
            return;
        }
    }
    
    State* ns = new DFAState();
    ns->setId(id);
    if(this->getAlphabet() != nullptr){
        ns->setAlphabet(this->getAlphabet());
    }
    ns->setInit();
    this->states.insert(ns);
    this->initState = ns;
}


void DFA::addAccState(int id){
    for(State* state : this->states){
        if(state->getId() == id){
            std::cout << "add init state error, state already exists" << std::endl;
            return;
        }
    }
    
    State* ns = new DFAState();
    ns->setId(id);
    if(this->getAlphabet() == nullptr){
        ns->setAlphabet(this->getAlphabet());
    }
    ns->setAcc();
    this->states.insert(ns);
    this->accStates.insert(ns);
}


void DFA::addInitAccState(int id){
    for(State* state : this->states){
        if(state->getId() == id){
            std::cout << "add init state error, state already exists" << std::endl;
            return;
        }
    }
    
    State* ns = new DFAState();
    ns->setId(id);
    
    if(this->getAlphabet() == nullptr){
        ns->setAlphabet(this->getAlphabet());
    }
    ns->setAcc();
    ns->setInit();
    this->states.insert(ns);
    this->accStates.insert(ns);
    this->initState = ns;
}


void DFA::delState(int id){
    if(!this->hasState(id)){
        std::cout << "del state error, state not exists" << std::endl;
        return;
    }
    for(State* state : this->states){
        if(state->getId() == id){
            this->states.erase(state);
            if(state->isAccState()){
                this->states.erase(state);
            }
            if(state->isInitialState()){
                this->initState = nullptr;
            }
            delete(state);
            break;
        }
    }
}




void DFA::addTransition(int fromId, Letter* l, int toId){
    if(l->getAlphabet() != this->alphabet){
        std::cout << "add transition error, inconsistent alphabet" << std::endl;
        return;
    }
    if(this->hasTransition(fromId, l, toId)){
        std::cout << "add transition error, transition exists" << std::endl;
        return;
    }
    DFATrans* dfat = new DFATrans(this->getState(fromId), l, this->getState(toId));

    this->transitions.insert(dfat);

    this->getState(fromId)->addTransition(dfat);
}


void DFA::delTransition(int fromId, Letter* l, int toId){
    if(!this->hasTransition(fromId, l, toId)){
        std::cout << "del transition error, transition not exists" << std::endl;
        return;
    }
    Transition* tranTemp;
    for(Transition* tran : this->transitions){
        if(tran->getFromState()->getId() == fromId &&
           tran->getToState()->getId() == toId &&
           tran->getLetter()->getId() == l->getId()){
            tranTemp = tran;
            this->transitions.erase(tran);
            tran->getFromState()->delTransition(tran);
            break;
        }
    }


}



Path* DFA::runOnWordOutPath(Word* word){
    if(word->getAlphabet() != this->alphabet){
        std::cout << "run on word error, alphabet not consistent" << std::endl;
        return nullptr;
    }
    Path* path = new Path(word);
    DFAState* currentState = (DFAState*)this->initState;
    DFAState* temp = currentState;
    path->appendStemState(temp);
    for(Letter* l : word->getWordStem()){
        currentState = this->executeLetter(currentState, l);
        DFAState* tempState = currentState;
        path->appendStemState(tempState);
    }
    return path;
}


bool DFA::runOnWordOutResult(Word* word){
    if(word->getAlphabet() != this->alphabet){
        std::cout << "run on word error, alphabet not consistent" << std::endl;
        return false;
    }
    DFAState* currentState = (DFAState*)this->initState;
    for(Letter* l : word->getWordStem()){
        currentState = this->executeLetter(currentState, l);
    }
    if(currentState->isAccState()){
        return true;
    } else {
        return false;
    }
}


std::set<State*>& DFA::getStates(){
    return this->states;
}


State* DFA::getInitState(){
    return this->initState;
}


std::set<State*>& DFA::getAccStates(){
    return this->accStates;
}


DFAState* DFA::executeLetter(DFAState* currentState, Letter* l){
    return currentState->executeLetter(l);
}


}