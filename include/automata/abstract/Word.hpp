#ifndef Word_hpp
#define Word_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../alphabet/Alphabet.hpp"
namespace llvmadt
{
template<class A>
class Word
{
protected:
    std::list<Letter<A>*> wordStem;
    std::list<Letter<A>*> wordLoop;
    Alphabet<A>* alphabet;
public:
    Word(/* args */);
    ~Word();
    std::list<Letter<A>*>& getWordStem();
    std::list<Letter<A>*>& getWordLoop();
    void delStemLetter(int pos);
    void appendStemLetter(Letter<A>* letter);
    Letter<A>& getStemLetter(int pos);
    void delLoopLetter(int pos);
    void appendLoopLetter(Letter<A>* letter);
    Letter<A>& getLoopLetter(int pos);
    Alphabet<A>& getAlphabet();
    void setAlphabet(Alphabet<A>* alpha);
    bool isFinite();
    std::string toString();
    
};

} // namespace llvmadt





#endif
