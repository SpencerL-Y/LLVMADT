#include "../../../include/automata/abstract/Path.hpp"


namespace llvmadt{
    

Path::Path(){
    this->word = new Word();
}



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



Word* Path::getLoopWord(){
    return this->word;
}

std::string Path::toString(){
    std::string outStr = "";
    
}

}