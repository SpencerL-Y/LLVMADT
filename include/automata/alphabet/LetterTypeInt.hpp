#ifndef LetterTypeInt_hpp
#define LetterTypeInt_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./LetterType.hpp"
namespace llvmadt{



class LetterTypeInt : public LetterType
{
private:
    int content;
public:
    std::string toString();
    int getContent();
    void setContent(int content);
    LetterTypeInt(/* args */);
    ~LetterTypeInt();
};

}

#endif