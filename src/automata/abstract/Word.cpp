#include "../../../include/automata/abstract/Word.hpp"


namespace llvmadt{
    
template<class A>
Word<A>::Word(){

}


template<class A>
Word<A>::~Word(){

}


template<class A>
std::list<Letter<A>*>& Word<A>::getWordStem(){
    return this->wordStem;
}


template<class A>
std::list<Letter<A>*>& Word<A>::getWordLoop(){
    return this->wordLoop;
}


template<class A>
void Word<A>::delStemLetter(int pos){
    this->wordStem.erase(pos);
}


template<class A>
void Word<A>::appendStemLetter(Letter<A>* letter){
    if(letter->getAlphabet() == this->getAlphabet){
        this->wordStem.push_back(letter);
    } else {
        std::cout << "appendStemLetter error, alphabet inconsistent" << std::endl;
    }
}


template<class A>
Letter<A>& Word<A>::getStemLetter(int pos){
    return this->wordStem[pos];
}



template<class A>
void Word<A>::delLoopLetter(int pos){
    this->wordStem.erase(pos);
}


template<class A>
void Word<A>::appendLoopLetter(Letter<A>* letter){
    if(letter->getAlphabet() == this->getAlphabet){
        this->wordLoop.push_back(letter);
    } else {
        std::cout << "appendStemLetter error, alphabet inconsistent" << std::endl;
    }
}


template<class A>
Letter<A>& Word<A>::getLoopLetter(int pos){
    return this->wordLooph[pos];
}


}