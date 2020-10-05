#include "../../../include/automata/alphabet/Letter.hpp"


namespace llvmadt{
    template <class A>
    int Letter<A>::getId(){
        return this->id;
    }
    template <class A>
    void Letter<A>::setId(int id){
        this->id = id;
    }

    template <class A>
    void Letter<A>::setContent(A* content){
        if(this->content != nullptr){
            delete(content);
        }
        this->content = content;
    }

    template <class A>
    A* Letter<A>::getContent(){
        return this->content;
    }

    template <class A>
    std::string Letter<A>::toString(){
        std::string result = "Letter:{";
        result += this->content->toString();
        result += "}";
        return result;
    }

    template <class A>
    Letter<A>::Letter(){

    }

    template <class A>
    Letter<A>::~Letter(){
        delete(this->content);
    }

}