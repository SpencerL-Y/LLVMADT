
#include "../../include/cfa/Z3Test.hpp"
namespace llvmadt{

Z3Test::Z3Test(){

}

Z3Test::~Z3Test(){
    
}

void Z3Test::testFunction(){
    z3::context c;
    z3::expr myIntExpr = c.int_const("x");

}

}
