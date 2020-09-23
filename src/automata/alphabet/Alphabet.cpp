#include "../../../include/automata/alphabet/Alphabet.hpp"

namespace llvmadt{
    template <class A>
    Alphabet<A>::Alphabet(){

    }

    template <class A>
    void Alphabet<A>::addLetter(A* content){
        Letter<A>* nl = new Letter<A>();
        nl->setId(this->letters.size());
        this->letters.push_back(nl);
    }

    template <class A>
    Letter<A>* Alphabet<A>::getLetter(int id){
        for(Letter<A>* l : this->letters){
            if(l->getId() == id){
                return l;
            }
        }
    }

    template <class A>
    std::string Alphabet<A>::toString(){
        std::string result = "Alphabet: {";
        int i = 0;
        for(Letter<A>* l : this->letters){
            result += l->toString();
            if(i < this->letters.size() - 1){
                result += ", ";
            }
            i ++;
        }
        result += "}\n";
        return result;
    }

    template <class A>
    Alphabet<A>::~Alphabet(){
        for(Letter<A>* l : this->letters){
            delete(l);
        }
    }
}