#ifndef Word_hpp
#define Word_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "../alphabet/Alphabet.hpp"
namespace llvmadt
{

class Word
{
protected:
    std::vector<Letter*> wordStem;
    std::vector<Letter*> wordLoop;
    Alphabet* alphabet;
public:
    Word(/* args */);
    ~Word();
    std::vector<Letter*>& getWordStem();
    std::vector<Letter*>& getWordLoop();
    void delStemLetter(int pos);
    void appendStemLetter(Letter* letter);
    Letter* getStemLetter(int pos);
    void delLoopLetter(int pos);
    void appendLoopLetter(Letter* letter);
    Letter* getLoopLetter(int pos);
    Alphabet* getAlphabet();
    void setAlphabet(Alphabet* alpha);
    bool isFinite();
    std::string toString();
    
};

} // namespace llvmadt





#endif
