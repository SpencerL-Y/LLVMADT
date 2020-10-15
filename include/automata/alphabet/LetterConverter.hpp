#ifndef LetterConverter_hpp
#define LetterConverter_hpp
#include <stdlib.h>
#include <iostream>
#include <list>
#include <vector>
#include "./LetterTypeInst.hpp"
#include "./LetterTypeZ3Expr.hpp"
namespace llvmadt
{
    class LetterConverter
    {
    private:
        /* data */
    public:
        LetterConverter(/* args */);
        ~LetterConverter();
        LetterTypeZ3Expr* fromInst2Z3Expr(LetterTypeInst* instLetterType);

    };  
} // namespace llvmadt


#endif