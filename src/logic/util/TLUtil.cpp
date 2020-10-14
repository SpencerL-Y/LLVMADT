#include "../../../include/logic/util/TLUtil.hpp"

namespace llvmadt
{
    TLUtil::TLUtil(/* args */)
    {
    }
    
    TLUtil::TLUtil(z3::context* c){
        this->c = c;
    }

    TLUtil::~TLUtil()
    {
    }

    
    z3::context* TLUtil::getContext(){
        return this->c;
    }

    void TLUtil::setContext(z3::context* c){
        this->c = c;
    }

    bool TLUtil::isSimpleLTL(spot::formula& f){
        if(f.kind() == spot::op::ap){
            return true;
        } else if(f.kind() == spot::op::G || f.kind() == spot::op::F){
            spot::formula f0 = f[0];
            return this->isSimpleLTL(f0);
        }
        // TODO: this part is harder, to be added lat er
        /* else if(f.kind() == spot::op::And || f.kind() == spot::op::Or){
            bool result = true;
            for(spot::formula child : f){
                result &= isSimpleLTL(child);
                if(result == false){
                    return result;
                }
            }
            return result;
        } */
        else {
            return false;
        }
    }

    SimpleType TLUtil::getSimpleType(spot::formula& pf){
        if(pf.kind() == spot::op::ap){
            return SimpleType::AP;
        } else if(pf.kind() == spot::op::F){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::ap){
                return SimpleType::F;
            } else if(f0.kind() == spot::op::G){
                spot::formula f1 = f0[0];
                if(f1.kind() == spot::op::ap){
                    return SimpleType::FG;
                } else {
                    return SimpleType::None;
                }
            } else {
                return SimpleType::None;
            }
        } else if(pf.kind() == spot::op::G){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::ap){
                return SimpleType::G;
            } else if(f0.kind() == spot::op::F){
                spot::formula f1 = f0[0];
                if(f1.kind() == spot::op::ap){
                    return SimpleType::GF;
                } else {
                    return SimpleType::None;
                }
            } else {
                return SimpleType::None;
            }
        } else {
            return SimpleType::None;
        }
    }


    z3::expr TLUtil::extractSimpleFormula_F(spot::formula& pf){
        if(pf.kind() == spot::op::F){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::ap){
                z3::expr z3f = this->c->int_const(f0.ap_name().c_str());
                return z3f;
            }
        }
    }

    z3::expr TLUtil::extractSimpleFormula_FG(spot::formula& pf){
        if(pf.kind() == spot::op::F){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::G){
                spot::formula f1 = f0[0];
                if(f1.kind() == spot::op::ap){
                    z3::expr z3f = this->c->int_const(f1.ap_name().c_str());
                    return z3f;
                }
            }
        }
    }

    z3::expr TLUtil::extractSimpleFormula_G(spot::formula& pf){
        if(pf.kind() == spot::op::G){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::ap){
                z3::expr z3f = this->c->int_const(f0.ap_name().c_str());
                return z3f;
            }
        }
    }

    z3::expr TLUtil::extractSimpleFormula_GF(spot::formula& pf){
        if(pf.kind() == spot::op::G){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::F){
                spot::formula f1 = f0[0];
                if(f1.kind() == spot::op::ap){
                    z3::expr z3f = this->c->int_const(f1.ap_name().c_str());
                    return z3f;
                }
            }
        }
    }


    void TLUtil::addApZ3ExprMap(std::string apStr, z3::expr* z3Expression){
        std::pair<std::string, z3::expr*> p;
        p.first = apStr;
        p.second = z3Expression;
        this->apStr2Z3ExprMap.insert(p);
    }

    z3::expr* TLUtil::mapApStr2Z3Expr(std::string apStr){
        auto i = this->apStr2Z3ExprMap.find(apStr);
        if(i != this->apStr2Z3ExprMap.end()){
            return i->second;
        } else {
            std::cout << "error: ap str not found" << std::endl;
            return nullptr;
        }
    }
} // namespace llvmadt
