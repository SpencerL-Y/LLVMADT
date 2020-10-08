#include "../../../include/automata/abstract/Path.hpp"


namespace llvmadt{
    

Path::Path(){
    this->word = new Word();
}



Path::Path(Alphabet* alpha){
    this->alphabet = alpha;
    this->word = new Word();
}


Path::Path(Word* word){
    this->alphabet = word->getAlphabet();
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
    if(letter->getAlphabet() == this->getAlphabet()){
        this->word->appendStemLetter(letter);
    } else {
        std::cout << "append stem letter error, alphabet inconsistent" << std::endl;
    }
}


void Path::appendStemState(State* state){
    if(state->getAlphabet() == this->alphabet){
        this->stemStates.push_back(state);
    } else {
         std::cout << "append stem state error, alphabet inconsistent" << std::endl;
    }
}



Word* Path::getStemWord(){
    return this->word;
}



std::vector<State*>& Path::getLoopStates(){
    return this->loopStates;
}


State* Path::getLoopState(int pos){
    return this->loopStates[pos];
}


void Path::appendLoopLetter(Letter* letter){
    if(letter->getAlphabet() == this->getAlphabet()){
        this->word->appendLoopLetter(letter);
    } else {
        std::cout << "append loop letter error, alphabet inconsistent" << std::endl;
    }
}


void Path::appendLoopState(State* state){
    if(state->getAlphabet() == this->alphabet){
        this->loopStates.push_back(state);
    } else {
         std::cout << "append loop state error, alphabet inconsistent" << std::endl;
    }
}



Word* Path::getLoopWord(){
    return this->word;
}


Alphabet* Path::getAlphabet(){
    return this->alphabet;
}


void Path::setAlphabet(Alphabet* alphabet){
    this->alphabet = alphabet;
}

std::string Path::toString(){
    
}

}