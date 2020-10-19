#include "../../../include/automata/abstract/Path.hpp"


namespace llvmadt{
    

Path::Path(){
    this->word = new Word();
}

Path::Path(Word* word){
    this->word = word;
}


Path::~Path(){
    delete(this->word);
}


std::vector<State*>& Path::getStemStates(){
    return this->stemStates;
}


State* Path::getStemState(int pos){
    return this->stemStates[pos];
}


void Path::appendStemLetter(Letter* letter){
    this->word->appendStemLetter(letter);
}


void Path::appendStemState(State* state){
    this->stemStates.push_back(state);
}



Word* Path::getWord(){
    return this->word;
}


std::vector<Letter*>& Path::getStemLetters(){
    return this->word->getWordStem();
}

std::vector<Letter*>& Path::getLoopLetters(){
    return this->word->getWordLoop();
}

Letter* Path::getStemLetter(int position){
    return this->word->getWordStem().at(position);
}
Letter* Path::getLoopLetter(int position){
    return this->word->getWordLoop().at(position);
}

std::vector<State*>& Path::getLoopStates(){
    return this->loopStates;
}


State* Path::getLoopState(int pos){
    return this->loopStates[pos];
}


void Path::appendLoopLetter(Letter* letter){
    this->word->appendLoopLetter(letter);
}


void Path::appendLoopState(State* state){
    this->loopStates.push_back(state);
}


std::map<std::string, int>& Path::getVarIndex(){
    return this->varIndex;
}

void Path::insertVarIndex(std::string varName){
    std::map<std::string, int>::iterator it = this->varIndex.find(varName);
    if(it == this->varIndex.end()){
        this->varIndex.insert(make_pair(varName, 0));
    } else {
        int oldIndex = it->second;
        this->varIndex.erase(varName);
        this->varIndex.insert(make_pair(varName, oldIndex + 1));
    }
    
}


int Path::getVarIndexVarName(std::string varName){
    std::map<std::string, int>::iterator it = this->varIndex.find(varName);
    if(it == this->varIndex.end()){
        return -1;
    } else {
        return it->second;
    }
}

Word* Path::getLoopWord(){
    return this->word;
}

std::string Path::toString(){
    std::string outStr = "";
    
}


std::map<std::string, int> Path::getCurrentVarIndex(int length){
    return this->varIndexArray[length];

}

std::vector<std::map<std::string, int>>& Path::getVarIndexArray(){
    return this->varIndexArray;
}

void Path::appendVarIndexArray(std::map<std::string, int>& currentVarIndex){
    this->varIndexArray.push_back(currentVarIndex);
}

}