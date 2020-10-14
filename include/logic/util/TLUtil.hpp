#ifndef TLUtil_hpp
#define TLUtil_hpp

#include <stdlib.h>
#include <vector>
#include <list>
#include <iostream>
#include <spot/tl/parse.hh>

#include <spot/twaalgos/translate.hh>
#include <spot/twaalgos/hoa.hh>
#include <z3++.h>
// this file is used for utility of manipulating the temperal logic
namespace llvmadt
{
    enum class SimpleType {
        AP, F, FG, GF, G, None
    };

    class TLUtil
    {
    private:
        z3::context* c;
        // this is a map the ap name of LTL formula to the z3 expression used for verification
        std::map<std::string, z3::expr*> apStr2Z3ExprMap;
    public:
        /*To judge whether the formula is of the form: p::= Gp, Not p, Fp */
        bool isSimpleLTL(spot::formula& pf);
        SimpleType getSimpleType(spot::formula& pf);
        z3::expr extractSimpleFormula_F(spot::formula& pf);
        z3::expr extractSimpleFormula_GF(spot::formula& pf);
        z3::expr extractSimpleFormula_FG(spot::formula& pf);
        z3::expr extractSimpleFormula_G(spot::formula& pf);
        bool isGp(spot::formula& pf);
        bool isFp(spot::formula& pf);
        bool isGFp(spot::formula& pf);
        bool isFGp(spot::formula& pf);

        z3::context* getContext();
        void setContext(z3::context* c);
        void addApZ3ExprMap(std::string apStr, z3::expr* z3Expression);
        TLUtil(z3::context* c);
        TLUtil();
        ~TLUtil();
    };
    
    

} // namespace llvmadt



#endif