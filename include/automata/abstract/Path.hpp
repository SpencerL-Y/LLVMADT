#ifndef Path_hpp
#define Path_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./State.hpp"
#include "./Word.hpp"

namespace llvmadt{

template <class A>
class Path
{
protected:
    std::list<State<A>*> stemStates;
    std::list<State<A>*> loopStates;
    Word<A>* word;
    Alphabet<A>* alphabet;
    /* data */
public:
    Path(/* args */);
    Path(Alphabet<A>* alpha);
    Path(Word<A>* word);
    ~Path();
    std::list<State<A>*>& getStemStates();
    State<A>* getStemState(int pos);
    void appendStemLetter(Letter<A>* letter);
    void appendStemState(State<A>* state);
    Word<A>* getStemWord();


    std::list<State<A>*>& getLoopStates();
    State<A>* getLoopState(int pos);
    void appendLoopLetter(Letter<A>* letter);
    void appendLoopState(State<A>* state);
    Word<A>* getLoopWord();

    Alphabet<A>* getAlphabet();
    void setAlphabet(Alphabet<A>* alphabet);
    virtual std::string toString()=0;
};
}


#endif