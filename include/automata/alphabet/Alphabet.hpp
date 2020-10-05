#ifndef Alphabet_hpp
#define Alphabet_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <map>
#include <vector>

#include "./Letter.hpp"
namespace llvmadt{

template<class A>
class Alphabet
{
protected:
    std::map<std::string, Letter<A>*> letters;
public:
    void addLetter(A* content);
    Letter<A>* getLetter(int id);
    Letter<A>* getLetter(std::string keyStr);
    std::string toString();
    Alphabet(/* args */);
    ~Alphabet();
};
}


#endif
