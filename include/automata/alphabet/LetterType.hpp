#ifndef LetterType_hpp
#define LetterType_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
class LetterType
{
private:
    /* data */
public:
    virtual std::string toString();
    LetterType(/* args */);
    ~LetterType();
};



#endif