#include "../../../include/automata/alphabet/Alphabet.hpp"

namespace llvmadt{
    template <class A>
    Alphabet<A>::Alphabet(){

    }

    template <class A>
    void Alphabet<A>::addLetter(A* content){
        if(this->letters.find(content->toString()) != this->letters.end()){
            std::cout << "alphabet add letter error, key already exists" << std::endl;
            return;
        }
        Letter<A>* nl = new Letter<A>();
        nl->setId(this->letters.size());
        this->letters.push_back(nl);
    }

    template <class A>
    Letter<A>* Alphabet<A>::getLetter(int id){
        for(auto iter=this->letters.begin(); iter != this->letters.end(); ++iter){
            if(iter->second->getId() == id){
                return iter->second;
            }
        }
    }

    template <class A>
    Letter<A>* Alphabet<A>::getLetter(std::string keyStr){
        auto iter = this->letters.find(keyStr);
        if(iter != this->letters.end()){
            return iter->second;
        }
        return nullptr;
    }

    template <class A>
    std::string Alphabet<A>::toString(){
        std::string result = "Alphabet: {";
        int i = 0;
        for(auto iter = this->letters.begin(); iter != this-letters.end(); ++iter){
            result += iter->second->toString();
            if(i < this->letters.size() - 1){
                result += ", ";
            }
            i ++;
        }
        result += "}\n";
        return result;
    }
    template <class A>
    std::map<std::string, Letter<A>*>* Alphabet<A>::getLetters(){
        return &this->letters;
    }



    template <class A>
    int Alphabet<A>::getLettersSize(){
        return this->letters.size();
    }
    
    
    template <class A>
    Alphabet<A>::~Alphabet(){
        for(Letter<A>* l : this->letters){
            delete(l);
        }
    }
}