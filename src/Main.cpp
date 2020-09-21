#include <stdlib.h>
#include <stdio.h>
#include <iostream>

#include "../include/converter/Converter.hpp"
using namespace llvmadt;
int main(int argc, char** argv){
    Converter converter;
    converter.convertLLVM2CFAs(argv[1]);
    //CFA cfa;
    return 0;
}