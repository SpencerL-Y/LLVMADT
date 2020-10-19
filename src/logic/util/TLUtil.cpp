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

    bool TLUtil::isGp(spot::formula& pf){
        if(this->getSimpleType(pf) == SimpleType::G){
            return true;
        }
        return false;
    }

    bool TLUtil::isFp(spot::formula& pf){
        if(this->getSimpleType(pf) == SimpleType::F){
            return true;
        }
        return false;
    }

    bool TLUtil::isGFp(spot::formula& pf){
        if(this->getSimpleType(pf) == SimpleType::GF){
            return true;
        }
        return false;
    }

    bool TLUtil::isFGp(spot::formula& pf){
        if(this->getSimpleType(pf) == SimpleType::FG){
            return true;
        }
        return false;
    }

    z3::expr* TLUtil::extractSimpleFormula_F(spot::formula& pf){
        if(pf.kind() == spot::op::F){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::ap){
                z3::expr* z3f = this->mapApStr2Z3Expr(f0.ap_name());
                return z3f;
            } else {
                std::cout << "currently does not support" << std::endl;
                return nullptr;
            }
        } else {
                std::cout << "currently does not support" << std::endl;
                return nullptr;
        }
    }

    z3::expr* TLUtil::extractSimpleFormula_FG(spot::formula& pf){
        if(pf.kind() == spot::op::F){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::G){
                spot::formula f1 = f0[0];
                if(f1.kind() == spot::op::ap){
                    z3::expr* z3f = this->mapApStr2Z3Expr(f1.ap_name());
                    return z3f;
                } else {

                std::cout << "currently does not support" << std::endl;
                return nullptr;
                }
            } else {

                std::cout << "currently does not support" << std::endl;
                return nullptr;
            }
        } else {

                std::cout << "currently does not support" << std::endl;
                return nullptr;
        }
    }

    z3::expr* TLUtil::extractSimpleFormula_G(spot::formula& pf){
        z3::expr elF = this->c->bool_val(false);
        if(pf.kind() == spot::op::G){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::ap){
                z3::expr* z3f = this->mapApStr2Z3Expr(f0.ap_name());
                return z3f;
            } else {

                std::cout << "currently does not support" << std::endl;
                return nullptr;
            }
        } else {

                std::cout << "currently does not support" << std::endl;
                return nullptr;
        }
    }

    z3::expr* TLUtil::extractSimpleFormula_GF(spot::formula& pf){
        z3::expr elF = this->c->bool_val(false);
        if(pf.kind() == spot::op::G){
            spot::formula f0 = pf[0];
            if(f0.kind() == spot::op::F){
                spot::formula f1 = f0[0];
                if(f1.kind() == spot::op::ap){
                    z3::expr* z3f = this->mapApStr2Z3Expr(f1.ap_name());
                    return z3f;
                } else {

                std::cout << "currently does not support" << std::endl;
                return nullptr;
                }
            } else {

                std::cout << "currently does not support" << std::endl;
                return nullptr;
            }
        } else {

                std::cout << "currently does not support" << std::endl;
                return nullptr;
        }
    }


    void TLUtil::addApZ3ExprMap(std::string apStr, z3::expr* z3Expression){
        if(this->apStr2Z3ExprMap.find(apStr) != this->apStr2Z3ExprMap.end()){
            std::cout << "error apStr exists" << std::endl;
            return;
        } else {
            this->apStr2Z3ExprMap.insert(make_pair(apStr, z3Expression));
        }
        
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
