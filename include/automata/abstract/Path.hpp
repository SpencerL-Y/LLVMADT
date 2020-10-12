#ifndef Path_hpp
#define Path_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <set>
#include <vector>
#include "./State.hpp"
#include "./Word.hpp"

namespace llvmadt{


class Path
{
protected:
    std::vector<State*> stemStates;
    std::vector<State*> loopStates;
    Word* word;
    Alphabet* alphabet;
    /* data */
public:
    Path(/* args */);
    Path(Alphabet* alpha);
    Path(Word* word);
    ~Path();
    std::vector<State*>& getStemStates();
    State* getStemState(int pos);
    void appendStemLetter(Letter* letter);
    void appendStemState(State* state);
    Word* getWord();
    std::vector<Letter*>& getStemLetters();
    std::vector<Letter*>& getLoopLetters();
    Letter* getStemLetter(int position);
    Letter* getLoopLetter(int position);


    std::vector<State*>& getLoopStates();
    State* getLoopState(int pos);
    void appendLoopLetter(Letter* letter);
    void appendLoopState(State* state);
    Word* getLoopWord();

    Alphabet* getAlphabet();
    void setAlphabet(Alphabet* alphabet);
    std::string toString();
};
}


#endif