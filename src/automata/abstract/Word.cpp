#include "../../../include/automata/abstract/Word.hpp"


namespace llvmadt{
    

Word::Word(){

}



Word::~Word(){

}



std::vector<Letter*>& Word::getWordStem(){
    return this->wordStem;
}



std::vector<Letter*>& Word::getWordLoop(){
    return this->wordLoop;
}



void Word::delStemLetter(int pos){
    std::vector<Letter*>::iterator iter = this->wordStem.begin() + pos;
    this->wordStem.erase(iter);
}



void Word::appendStemLetter(Letter* letter){
    if(letter->getAlphabet() == this->getAlphabet()){
        this->wordStem.push_back(letter);
    } else {
        std::cout << "appendStemLetter error, alphabet inconsistent" << std::endl;
    }
}



Letter* Word::getStemLetter(int pos){
    return this->wordStem[pos];
}




void Word::delLoopLetter(int pos){
    std::vector<Letter*>::iterator iter = this->wordStem.begin() + pos;
    this->wordStem.erase(iter);
}



void Word::appendLoopLetter(Letter* letter){
    if(letter->getAlphabet() == this->getAlphabet()){
        this->wordLoop.push_back(letter);
    } else {
        std::cout << "appendStemLetter error, alphabet inconsistent" << std::endl;
    }
}

Alphabet* Word::getAlphabet(){
    return this->alphabet;
}


Letter* Word::getLoopLetter(int pos){
    return this->wordLoop[pos];
}


}