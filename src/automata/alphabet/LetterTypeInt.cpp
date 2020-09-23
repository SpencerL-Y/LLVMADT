#include "../../../include/automata/alphabet/LetterTypeInt.hpp"


namespace llvmadt{
    void LetterTypeInt::setContent(int content){
        this->content = content;
    }

    int LetterTypeInt::getContent(){
        return this->content;
    }

    std::string LetterTypeInt::toString(){
        return  std::to_string(this->content);
    }

    LetterTypeInt::LetterTypeInt(){

    }
    
    LetterTypeInt::~LetterTypeInt(){

    }

}