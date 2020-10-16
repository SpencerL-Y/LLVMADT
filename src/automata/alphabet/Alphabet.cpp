#include "../../../include/automata/alphabet/Alphabet.hpp"

namespace llvmadt{
    
    Alphabet::Alphabet(){

    }

    
    void Alphabet::addLetter(LetterType* content){
        //std::cout << content->toString();
        Letter* nl = new Letter();            
        nl->setId(this->letters.size());
  
        nl->setContent(content);
        nl->setAlphabet(this);
        //std::cout << content->toString() << std::endl;
        this->letters.insert(nl);
    }

    
    Letter* Alphabet::getLetter(int id){
        for(Letter* iter : this->letters){
            if(iter->getId() == id){
                return iter;
            }
        }
        return nullptr;
    }

    
    // std::string Alphabet::toString(){
    //     std::string result = "Alphabet: {";
    //     int i = 0;
    //     for(auto iter = this->letters.begin(); iter != this->letters.end(); ++iter){
    //         result += iter->second->toString();
    //         if(i < this->letters.size() - 1){
    //             result += ", ";
    //         }
    //         i ++;
    //     }
    //     result += "}\n";
    //     return result;
    // }
    
    std::set<Letter*>& Alphabet::getLetters(){
        return this->letters;
    }



    
    int Alphabet::getLettersSize(){
        return this->letters.size();
    }
    
    
    
    Alphabet::~Alphabet(){
        for(Letter* l : this->letters){
            delete(l);
        }
    }
}