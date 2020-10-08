#include "../../../include/automata/alphabet/Letter.hpp"


namespace llvmadt{
    
    int Letter::getId(){
        return this->id;
    }
    
    void Letter::setId(int id){
        this->id = id;
    }

    
    void Letter::setContent(LetterType* content){
        if(this->content != nullptr){
            delete(content);
        }
        this->content = content;
    }

    
    LetterType* Letter::getContent(){
        return this->content;
    }

    
    std::string Letter::toString(){
        std::string result = "Letter:{";
        result += this->content->toString();
        result += "}";
        return result;
    }

    Alphabet* Letter::getAlphabet(){
        return this->alpha;
    }
    
    Letter::Letter(){

    }

    
    Letter::~Letter(){
        delete(this->content);
    }

}