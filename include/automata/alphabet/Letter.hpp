#ifndef Letter_hpp
#define Letter_hpp

#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
namespace llvmadt{

template<class A> class Alphabet;
template<class A>
class Letter
{
protected:
    int id;
    A* content;
    Alphabet<A>* alpha;
public:
    int getId();
    void setId(int id);
    void setContent(A* content);
    A* getContent();
    std::string toString();
    Alphabet<A>* getAlphabet();
    Letter(/* args */);
    ~Letter();
};

}

#endif
