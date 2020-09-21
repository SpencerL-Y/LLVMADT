#include "../../include/cfa/Guard.hpp"


namespace llvmadt{
    std::string Guard::getGuardStr(){
        return this->guardStr;
    }

    void Guard::setGuardStr(std::string& str){
        this->guardStr = str;
    }

    std::string Guard::toString(){
        return nullptr;
    }

    Guard::Guard(){

    }

    Guard::~Guard(){
        
    }

}
