#include "../../../include/automata/abstract/Path.hpp"


namespace llvmadt{
    
template <class A>
Path<A>::Path(){
    this->word = new Word<A>();
}


template <class A>
Path<A>::Path(Alphabet<A>* alpha){
    this->alphabet = alpha;
    this->word = new Word<A>();
}

template <class A>
Path<A>::Path(Word<A>* word){
    this->alphabet = word->getAlphabet();
    this->word = word;
}

template <class A>
Path<A>::~Path(){
    delete(this->word);
}

template <class A>
std::list<State<A>*>& Path<A>::getStemStates(){
    return this->stemStates;
}

template <class A>
State<A>* Path<A>::getStemState(int pos){
    return this->stemStates[pos];
}

template <class A>
void Path<A>::appendStemLetter(Letter<A>* letter){
    if(letter->getAlphabet() == this->getAlphabet()){
        this->word->appendStemLetter(letter);
    } else {
        std::cout << "append stem letter error, alphabet inconsistent" << std::endl;
    }
}

template <class A>
void Path<A>::appendStemState(State<A>* state){
    if(state->getAlphabet() == this->alphabet){
        this->stemStates.push_back(state);
    } else {
         std::cout << "append stem state error, alphabet inconsistent" << std::endl;
    }
}


template <class A>
Word<A>* Path<A>::getStemWord(){
    return this->word;
}


template <class A>
std::list<State<A>*>& Path<A>::getLoopStates(){
    return this->loopStates;
}

template <class A>
State<A>* Path<A>::getLoopState(int pos){
    return this->LoopStates[pos];
}

template <class A>
void Path<A>::appendLoopLetter(Letter<A>* letter){
    if(letter->getAlphabet() == this->getAlphabet()){
        this->word->appendLoopLetter(letter);
    } else {
        std::cout << "append loop letter error, alphabet inconsistent" << std::endl;
    }
}

template <class A>
void Path<A>::appendLoopState(State<A>* state){
    if(state->getAlphabet() == this->alphabet){
        this->loopStates.push_back(state);
    } else {
         std::cout << "append loop state error, alphabet inconsistent" << std::endl;
    }
}


template <class A>
Word<A>* Path<A>::getLoopWord(){
    return this->word;
}

template <class A>
Alphabet<A>* Path<A>::getAlphabet(){
    return this->alphabet;
}

template <class A>
void Path<A>::setAlphabet(Alphabet<A>* alphabet){
    this->alphabet = alphabet;
}

}