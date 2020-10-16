#ifndef Alphabet_hpp
#define Alphabet_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>
#include <set>
#include <vector>

#include "./Letter.hpp"
#include "./LetterType.hpp"
#include "./LetterTypeZ3Expr.hpp"
namespace llvmadt{


class Alphabet
{
protected:
    std::set<Letter*> letters;
public:
    void addLetter(LetterType* content);
    Letter* getLetter(int id);
    std::set<Letter*>& getLetters();
    int getLettersSize();
    Alphabet(/* args */);
    ~Alphabet();
};
}


#endif
