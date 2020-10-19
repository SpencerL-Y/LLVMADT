#include "../../include/checker/PathChecker.hpp"
namespace llvmadt
{
    PathChecker::PathChecker(/* args */)
    {
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

    bool PathChecker::checkFinitePathProperty(Path* path, std::string ltlStr){
        // return  true if the path satisfy the ltl formula 
        // false if the path is infeasible or the property is violated OR the formula is too complex
        spot::parsed_formula pf = spot::parse_infix_psl(ltlStr);
        spot::formula f = pf.f;
        TLUtil tlutil;
        if(tlutil.isSimpleLTL(f)){
            if(tlutil.isFp(f)){
                z3::expr* prop = tlutil.extractSimpleFormula_F(f);
                std::string varName = prop->to_string();
                z3::context* ctx = ((LetterTypeZ3Expr*)path->getStemLetter(0))->getContext();
                z3::expr tempFormula = ctx->bool_val(true);
                int max = path->getVarIndexVarName(varName);
                z3::expr_vector vec_origin(*ctx);
                vec_origin.push_back(*prop);
                for(int i = 0; i <= max; i++){
                    z3::expr_vector vec_subs(*ctx);
                    vec_subs.push_back(ctx->int_const((varName + std::to_string(i)).c_str()));
                    tempFormula = tempFormula || prop->substitute(vec_origin, vec_subs);
                }
                std::cout << "tempFormula: " << tempFormula.to_string() << std::endl;
                z3::solver solver(*ctx);
                tempFormula = tempFormula && (!*prop);
                solver.add(tempFormula);
                if(solver.check() == z3::unsat){
                    return true;
                }
                for(Letter* l : path->getStemLetters()){
                    solver.add(*((LetterTypeZ3Expr*)l)->getExpression());
                    if(solver.check() == z3::unsat){
                        return true;
                    }
                }
                return false;
            } else if(tlutil.isGp(f)){
                z3::expr* prop = tlutil.extractSimpleFormula_G(f);
                z3::context* ctx = ((LetterTypeZ3Expr*)path->getStemLetter(0))->getContext();
                z3::expr tempFormula = ctx->bool_val(true) && *prop;
                z3::solver solver(*ctx);
                solver.add(tempFormula);
                if(solver.check() == z3::unsat){
                    return false;
                }
                for(Letter* l : path->getStemLetters()){
                    solver.add(*((LetterTypeZ3Expr*)l)->getExpression());
                    if(solver.check() == z3::unsat){
                        return false;
                    }
                }
                return true;
            } else if(tlutil.isGFp(f)){
                z3::expr* prop = tlutil.extractSimpleFormula_GF(f);
                z3::context* ctx = ((LetterTypeZ3Expr*)path->getStemLetter(0))->getContext();
                z3::expr tempFormula = ctx->bool_val(true);
                z3::solver solver(*ctx);
                LetterTypeZ3Expr* l  = ((LetterTypeZ3Expr*)path->getStemLetters().at(path->getStemLetters().size() - 1));
                solver.add(*l->getExpression());
                solver.add(!*prop);
                if(solver.check() == z3::unsat){
                    return true;
                } else {
                    return false;
                }
            } else if(tlutil.isFGp(f)){
                z3::expr* prop = tlutil.extractSimpleFormula_FG(f);
                z3::context* ctx = ((LetterTypeZ3Expr*)path->getStemLetter(0))->getContext();
                z3::expr tempFormula = ctx->bool_val(true);
                z3::solver solver(*ctx);
                LetterTypeZ3Expr* l  = ((LetterTypeZ3Expr*)path->getStemLetters().at(path->getStemLetters().size() - 1));
                solver.add(*l->getExpression());
                solver.add(!*prop);
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
} // namespace llvmadt
