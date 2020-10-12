#ifndef Letter_hpp
#define Letter_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./LetterType.hpp"

namespace llvmadt{

class Alphabet;

class Letter
{
protected:
    int id;
    LetterType* content;
    Alphabet* alpha;
public:
    int getId();
    void setId(int id);
    void setContent(LetterType* content);
    LetterType* getContent();
    std::string toString();
    Alphabet* getAlphabet();
    void setAlphabet(Alphabet* alpha);
    Letter(/* args */);
    ~Letter();
};

}

#endif
