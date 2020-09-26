#ifndef LetterTypeChar_hpp
#define LetterTypeChar_hpp


#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./LetterType.hpp"
namespace llvmadt{



class LetterTypeChar : public LetterType
{
private:
    char content;
public:
    std::string toString();
    int getContent();
    void setContent(char content);
    LetterTypeChar(/* args */);
    LetterTypeChar(char content);
    ~LetterTypeChar();
};

}

#endif