#ifndef Alphabet_hpp
#define Alphabet_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>

#include "./Letter.hpp"
namespace llvmadt{

template<class A>
class Alphabet
{
protected:
    std::list<Letter<A>*> letters;
public:
    void addLetter(A* content);
    Letter<A>* getLetter(int id);
    std::string toString();
    Alphabet(/* args */);
    ~Alphabet();
};
}


#endif
