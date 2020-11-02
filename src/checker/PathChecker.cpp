#include "../../include/checker/PathChecker.hpp"
namespace llvmadt
{
    PathChecker::PathChecker(/* args */TLUtil* ut, z3::context* c)
    {   
        if(ut->getContext() != c){
            std::cout << "error, context inconsistent" << std::endl;
            return;
        }
        this->tlutil = ut;
        this->tlutil->setContext(c);
    }
    
    PathChecker::~PathChecker()
    {
    }



    z3::solver* PathChecker::checkFinitePathFeasibility(Path* path){
        //return true if the path is feasible in the system
        z3::context* ctx = ((LetterTypeZ3Expr*)path->getStemLetter(0)->getContent())->getContext();
        z3::expr pathCondition = ctx->bool_val(1);
        z3::solver* solver = new z3::solver(*ctx);
        for(Letter* l : path->getStemLetters()){
            //conjunct all the edge transition guard into a path condition formula
            pathCondition = pathCondition && *((LetterTypeZ3Expr*)l->getContent())->getExpression();
        }
        solver->add(pathCondition);
        if(solver->check() == z3::unsat){
            delete(solver);
            return nullptr;
        } else {
            return solver;
        }
    }

    bool PathChecker::checkFinitePathProperty(Path* path, std::string ltlStr, std::set<std::string> varNames){
        // return  true if the path satisfy the ltl formula 
        // false if the path is infeasible or the property is violated OR the formula is too complex
        spot::parsed_formula pf = spot::parse_infix_psl(ltlStr);
        spot::formula f = pf.f;
        std::cout << "ltl parsed" << std::endl;
        if(tlutil->isSimpleLTL(f)){
            std::cout << "is simple ltl" << std::endl;
            if(tlutil->isFp(f)){
                std::cout << "check F property" << std::endl;
                z3::expr* prop = tlutil->extractSimpleFormula_F(f);
                std::string varName = prop->to_string();
                z3::context* ctx = this->tlutil->getContext();
                //((LetterTypeZ3Expr*)path->getStemLetter(0))->getContext();
                // if(ctx == nullptr){
                //     std::cout << "what" << std::endl;
                // }
                z3::expr tempFormula = ctx->bool_val(true);
                z3::expr_vector vec_origin(*ctx);
                for(std::string varStr : varNames){
                    //std::cout << "wwwwww" << std::endl;
                    vec_origin.push_back(ctx->int_const(varStr.c_str()));
                }
                std::cout << "tempFormula: " << tempFormula.to_string() << std::endl;
                z3::solver solver(*ctx);
                solver.add(tempFormula);
                if(solver.check() == z3::unsat){
                    return true;
                }
                int length = 0;
                for(Letter* l : path->getStemLetters()){
                    z3::expr temptempForm = ctx->bool_val(true);
                    z3::expr_vector vec_curr(*ctx);
                    for(std::string varStr : varNames){
                        auto iter = path->getCurrentVarIndex(length).find(varStr);
                        if(iter == path->getCurrentVarIndex(length).end()){
                            //std::cout << "wwww " << varStr << std::endl;
                            vec_curr.push_back(ctx->int_const((varStr + "_" + std::to_string(0)).c_str()));
                        } else {
                            //std::cout << "wwwwww: " << varStr + std::to_string(iter->second) << std::endl;
                            vec_curr.push_back(ctx->int_const((varStr + "_" + std::to_string(iter->second)).c_str()));
                        }
                    }
                    std::cout << "origin: " << prop->to_string() << std::endl;
                    temptempForm = (!prop->substitute(vec_origin, vec_curr));
                    std::cout << "subs: " << temptempForm.to_string() << std::endl;
                    std::cout << "letter formula: " << (((LetterTypeZ3Expr*)l->getContent())->getExpression())->to_string()  << std::endl;
                    solver.add(*(((LetterTypeZ3Expr*)l->getContent())->getExpression()));
                    solver.push();
                    solver.add(temptempForm);
                    if(solver.check() == z3::unsat){

                        std::cout << "CHECKRESULT " << solver.check() << std::endl;
                        return true;
                    }
                    std::cout << "CHECKRESULT " << solver.check() << std::endl;
                    solver.pop();
                    length++;
                }
                return false;
            } else if(tlutil->isGp(f)){
                std::cout << "is G" << std::endl;
                z3::expr* prop = tlutil->extractSimpleFormula_G(f);
                std::cout << "prop: " << prop->to_string() << std::endl;
                z3::context* ctx = tlutil->getContext();
                z3::expr_vector vec_origin(*ctx);
                for(std::string varStr : varNames){
                    //std::cout << "wwwwww" << std::endl;
                    vec_origin.push_back(ctx->int_const(varStr.c_str()));
                }
                z3::expr tempFormula = ctx->bool_val(true);
                z3::solver solver(*ctx);
                solver.add(tempFormula);
                int length = 0;
                for(Letter* l : path->getStemLetters()){
                    z3::expr_vector vec_curr(*ctx);
                    for(std::string varStr : varNames){
                        auto iter = path->getCurrentVarIndex(length).find(varStr);
                        if(iter == path->getCurrentVarIndex(length).end()){
                            //std::cout << "wwww " << varStr << std::endl;
                            vec_curr.push_back(ctx->int_const((varStr + std::to_string(0)).c_str()));
                        } else {
                            //std::cout << "wwwwww: " << varStr + std::to_string(iter->second) << std::endl;
                            vec_curr.push_back(ctx->int_const((varStr + std::to_string(iter->second)).c_str()));
                        }
                    }
                    tempFormula = (!prop->substitute(vec_origin, vec_curr));
                    std::cout << "temp: " << tempFormula.to_string() << std::endl;
                    solver.add(*((LetterTypeZ3Expr*)l->getContent())->getExpression());
                    solver.push();
                    solver.add(tempFormula);
                    if(solver.check() == z3::sat){
                        return false;
                    }
                    solver.pop();
                    length++;
                }
                return true;
            } else if(tlutil->isGFp(f)){
                z3::expr* prop = tlutil->extractSimpleFormula_GF(f);
                z3::context* ctx = tlutil->getContext();
                z3::expr_vector vec_origin(*ctx);
                for(std::string varStr : varNames){
                    //std::cout << "wwwwww" << std::endl;
                    vec_origin.push_back(ctx->int_const(varStr.c_str()));
                }
                z3::expr_vector vec_replaced(*ctx);
                for(std::string varStr : varNames){
                    auto iter = path->getVarIndex().find(varStr);
                    if(iter == path->getVarIndex().end()){
                        vec_replaced.push_back(ctx->int_const((varStr + std::to_string(0)).c_str()));
                    } else {
                        vec_replaced.push_back(ctx->int_const((varStr + std::to_string(iter->second)).c_str()));
                    }
                }
                z3::expr tempFormula = prop->substitute(vec_origin, vec_replaced);
                z3::solver solver(*ctx);
                for(Letter* l : path->getStemLetters()){
                    solver.add(*((LetterTypeZ3Expr*)l->getContent())->getExpression());
                }
                solver.add(!tempFormula);
                if(solver.check() == z3::unsat){
                    return true;
                } else {
                    return false;
                }
            } else if(tlutil->isFGp(f)){
                z3::expr* prop = tlutil->extractSimpleFormula_FG(f);
                z3::context* ctx = tlutil->getContext();
                z3::expr_vector vec_origin(*ctx);
                for(std::string varStr : varNames){
                    //std::cout << "wwwwww" << std::endl;
                    vec_origin.push_back(ctx->int_const(varStr.c_str()));
                }
                z3::expr_vector vec_replaced(*ctx);
                for(std::string varStr : varNames){
                    auto iter = path->getVarIndex().find(varStr);
                    if(iter == path->getVarIndex().end()){
                        vec_replaced.push_back(ctx->int_const((varStr + std::to_string(0)).c_str()));
                    } else {
                        vec_replaced.push_back(ctx->int_const((varStr + std::to_string(iter->second)).c_str()));
                    }
                }
                z3::expr tempFormula = prop->substitute(vec_origin, vec_replaced);
                z3::solver solver(*ctx);
                for(Letter* l : path->getStemLetters()){
                    solver.add(*((LetterTypeZ3Expr*)l->getContent())->getExpression());
                }

                solver.add(!tempFormula);
                if(solver.check() == z3::unsat){
                    return true;
                } else {
                    return false;
                }
            } else {
                std::cout << "path property checking error: property too complex." << std::endl;
                return false;
            }
        } else {
            std::cout << "path property checking error: property too complex." << std::endl;
            return false;
        }
    }


    void PathChecker::addTLUtilApStrMap(std::string apStr, z3::expr* exp){
        this->tlutil->addApZ3ExprMap(apStr, exp);
    }
} // namespace llvmadt
