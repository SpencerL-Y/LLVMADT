#ifndef LetterType_hpp
#define LetterType_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
namespace llvmadt{

class LetterType
{
private:
    /* data */
public:
    virtual std::string toString()=0;
    LetterType(/* args */);
    ~LetterType();
};


}

#endif