#include "../../../include/automata/alphabet/Alphabet.hpp"

namespace llvmadt{
    
    Alphabet::Alphabet(){

    }

    
    void Alphabet::addLetter(LetterType* content){
        if(this->letters.find(content->toString()) != this->letters.end()){
            std::cout << "alphabet add letter error, key already exists" << std::endl;
            return;
        }
        Letter* nl = new Letter();
        nl->setId(this->letters.size());
        nl->setContent(content);
        nl->setAlphabet(this);
        this->letters[content->toString()] = nl;
    }

    
    Letter* Alphabet::getLetter(int id){
        for(auto iter=this->letters.begin(); iter != this->letters.end(); ++iter){
            if(iter->second->getId() == id){
                return iter->second;
            }
        }
    }

    
    Letter* Alphabet::getLetter(std::string keyStr){
        auto iter = this->letters.find(keyStr);
        if(iter != this->letters.end()){
            return iter->second;
        }
        return nullptr;
    }

    
    std::string Alphabet::toString(){
        std::string result = "Alphabet: {";
        int i = 0;
        for(auto iter = this->letters.begin(); iter != this->letters.end(); ++iter){
            result += iter->second->toString();
            if(i < this->letters.size() - 1){
                result += ", ";
            }
            i ++;
        }
        result += "}\n";
        return result;
    }
    
    std::map<std::string, Letter*>& Alphabet::getLetters(){
        return this->letters;
    }



    
    int Alphabet::getLettersSize(){
        return this->letters.size();
    }
    
    
    
    Alphabet::~Alphabet(){
        for(auto iter = this->letters.begin(); iter != this->letters.end(); ++iter){
            delete(iter->second);
        }
    }
}