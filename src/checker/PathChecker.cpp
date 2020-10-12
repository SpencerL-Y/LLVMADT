#include "../../include/checker/PathChecker.hpp"
namespace llvmadt
{
    PathChecker::PathChecker(/* args */)
    {
    }
    
    PathChecker::~PathChecker()
    {
    }



    z3::model* PathChecker::checkPathFeasibility(Path& path){
        //return true if the path is feasible in the system
        z3::context* ctx = ((LetterTypeZ3Expr*)path.getStemLetter(0))->getContext();
        z3::expr pathCondition = ctx->bool_val(true);
        for(Letter* l : path.getStemLetters()){
            //conjunct all the edge transition guard into a path condition formula
            pathCondition = pathCondition && ((LetterTypeZ3Expr*)l)->getExpression();
        }
        z3::solver solver(*ctx);
        solver.add(pathCondition);
        if(solver.check() == z3::unsat){
            return nullptr;
        } else {
            return &solver.get_model();
        }
    }

    bool PathChecker::checkPathProperty(Path& path, std::string ltlStr){
        // return  true if the path satisfy the ltl formula 
        // false if the path is infeasible or the property is violated OR the formula is too complex
        spot::parsed_formula pf = spot::parse_infix_psl(ltlStr);
        spot::formula f = pf.f;
        TLUtil tlutil;
        if(tlutil.isSimpleLTL(f)){
            if(tlutil.isFp(f)){
                z3::expr prop = tlutil.extractSimpleFormula_F(f);
                z3::context* ctx = ((LetterTypeZ3Expr*)path.getStemLetter(0))->getContext();
                z3::expr tempFormula = ctx->bool_val(true);
                z3::solver solver(*ctx);
                tempFormula = tempFormula && (!prop);
                solver.add(tempFormula);
                if(solver.check() == z3::unsat){
                    return true;
                }
                for(Letter* l : path.getStemLetters()){
                    solver.add(*((LetterTypeZ3Expr*)l)->getExpression());
                    if(solver.check() == z3::unsat){
                        return true;
                    }
                }
                return false;
            } else if(tlutil.isGp(f)){
                z3::expr prop = tlutil.extractSimpleFormula_G(f);
                z3::context* ctx = ((LetterTypeZ3Expr*)path.getStemLetter(0))->getContext();
                z3::expr tempFormula = ctx->0

            } else if(tlutil.isGFp(f)){
                z3::expr prop = tlutil.extractSimpleFormula_GF(f);
            } else if(tlutil.isFGp(f)){
                z3::expr prop = tlutil.extractSimpleFormula_FG(f);
            } else {
                std::cout << "path property checking error: property too complex." << std::endl;
                return nullptr;
            }
        } else {
            std::cout << "path property checking error: property too complex." << std::endl;
            return nullptr;
        }
    }
} // namespace llvmadt
