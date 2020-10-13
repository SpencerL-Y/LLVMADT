#ifndef Alphabet_hpp
#define Alphabet_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "./Letter.hpp"
#include "./LetterType.hpp"
#include "./LetterTypeZ3Expr.hpp"
namespace llvmadt{


class Alphabet
{
protected:
    std::map<std::string, Letter*> letters;
public:
    void addLetter(LetterType* content);
    Letter* getLetter(int id);
    Letter* getLetter(std::string keyStr);
    std::map<std::string, Letter*>& getLetters();
    int getLettersSize();
    std::string toString();
    Alphabet(/* args */);
    ~Alphabet();
};
}


#endif
