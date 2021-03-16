//
// Created by center on 2021/3/14.
//

#include "../../include/execution-tree/InstructionParser.h"

namespace sym_exe {

    const int InstructionParser::INT = 1;
    const int InstructionParser::DOUBLE = 2;
    const int InstructionParser::UNKNOWN = 3;


    void InstructionParser::parse_single(InsPtr ins_ptr) {
//        llvm::errs() << *ins_ptr << " \t\t";
//        errs() << "var name: " << get_var_name(ins_ptr) << " constraint: ";
        get_constraint(ins_ptr);
        errs() << "\n";
    }

    std::string InstructionParser::get_var_name(InsPtr ins_ptr) {
        std::string var_name;
        if (const AllocaInst *AI = dyn_cast<AllocaInst>(ins_ptr)) {
            var_name = extract_name(AI);
        }
        if (const StoreInst *SI = dyn_cast<StoreInst>(ins_ptr)) {
            var_name = extract_name(SI);
        }
        if (const BranchInst *BI = dyn_cast<BranchInst>(ins_ptr)) {
            var_name = extract_name(BI);
        }
        if (const CmpInst *CI = dyn_cast<CmpInst>(ins_ptr)) {
            var_name = extract_name(CI);
        }
        if (const LoadInst *LI = dyn_cast<LoadInst>(ins_ptr)) {
            var_name = extract_name(LI);
        }
        return var_name;
    }

    z3::expr InstructionParser::get_constraint(InsPtr ins_ptr) {
        if (const StoreInst *SI = dyn_cast<StoreInst>(ins_ptr)) {
            return extract_constraints(SI);
        }
        if (const LoadInst *LI = dyn_cast<LoadInst>(ins_ptr)) {
            return extract_constraints(LI);
        }
        if (const BinaryOperator *BO = dyn_cast<BinaryOperator>(ins_ptr)) {
            return extract_constraints(BO);
        }
        if (const CmpInst *CI = dyn_cast<CmpInst>(ins_ptr)) {
            return extract_constraints(CI);
        }
        if (const PHINode *PHI = dyn_cast<PHINode>(ins_ptr)) {
            return extract_constraints(PHI);
        }
//        if (const BranchInst *branchInst = dyn_cast<BranchInst>(ins_ptr)) {
//            return extract_constraints(branchInst);
//        }
        if (const ReturnInst *returnInst = dyn_cast<ReturnInst>(ins_ptr)) {
            return extract_constraints(returnInst);
        }
        if (const AllocaInst *allocaInst = dyn_cast<AllocaInst>(ins_ptr)) {
            return extract_constraints(allocaInst);
        }
        errs() << "Unknown statement \n";
        return z3::expr(c);
    }

    std::string InstructionParser::extract_name(const BranchInst *ins_ptr) {
        if (ins_ptr->isConditional()) {
            return ins_ptr->getCondition()->getName();
        }
        return "";
    }

    std::string InstructionParser::extract_name(const AllocaInst *ins_ptr) {
        return ins_ptr->getName();
    }

    std::string InstructionParser::extract_name(const StoreInst *ins_ptr) {
        return ins_ptr->getPointerOperand()->getName();
    }

    std::string InstructionParser::extract_name(const CmpInst *ins_ptr) {
        return ins_ptr->getName();
    }

    std::string InstructionParser::extract_name(const LoadInst *ins_ptr) {
        return ins_ptr->getName();
    }

    z3::expr InstructionParser::extract_constraints(const StoreInst *ins_ptr) {
        const auto left = ins_ptr->getValueOperand();
        const auto right = ins_ptr->getPointerOperand();
        auto left_name = parse_llvm_value_to_string(left);
        auto right_name = parse_llvm_value_to_string(right);
        z3::expr right_expr = get_int_expr(right, true);
        z3::expr left_expr = get_int_expr(left);
        z3::expr ret = c.bool_val(true);
        ret = (right_expr == left_expr);
#ifdef DEBUG
        errs() << right_name << " = " << left_name << " expr: ";
        errs() << ret.to_string() << "\n";
#endif
        return ret;
    }

    z3::expr InstructionParser::extract_constraints(const LoadInst *ins_ptr) {
        std::string left_name = ins_ptr->getName();
        const auto right_name = ins_ptr->getPointerOperand()->getName();
        z3::expr left = get_int_expr(left_name, true);
        z3::expr right = get_int_expr(ins_ptr->getPointerOperand());
        z3::expr ret = c.bool_val(true);
        ret = (left == right);
#ifdef DEBUG
        errs() << left_name << " = " << right_name << " expr: ";
        errs() << ret.to_string() << "\n";
#endif
        return ret;
    }

    // unsigned cmp instructions may cause error
    // may use context to judge
    z3::expr InstructionParser::extract_constraints(const CmpInst *cmp_ptr) {
        z3::expr ret = c.bool_val(true);
        if (const auto *ins_ptr = dyn_cast<ICmpInst>(cmp_ptr)) {
            const auto op1 = parse_llvm_value_to_string(ins_ptr->getOperand(0));
            const auto op2 = parse_llvm_value_to_string(ins_ptr->getOperand(1));
            const std::string op = ins_ptr->getName();
            auto indexed_op = get_indexed_name(op, true);
            auto res = c.bool_const(indexed_op.c_str());
            auto num1 = get_int_expr(ins_ptr->getOperand(0));
            auto num2 = get_int_expr(ins_ptr->getOperand(1));
            switch (ins_ptr->getPredicate()) {
                case llvm::CmpInst::ICMP_EQ: {
                    ret = (res == (num1 == num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " = " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case llvm::CmpInst::ICMP_NE: {
                    ret = (res == (num1 != num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " != " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_UGT: {
                    ret = (res == (num1 >= num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " >= " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_UGE: {
                    ret = (res == (num1 != num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " != " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_ULT: {
                    ret = (res == (num1 < num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " < " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_ULE: {
                    ret = (res == (num1 <= num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " <= " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_SGT: {
                    ret = (res == (num1 > num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " > " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_SGE: {
                    ret = (res == (num1 >= num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " >= " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_SLT: {
                    ret = (res == (num1 < num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " < " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_SLE: {
                    ret = (res == (num1 <= num2));
#ifdef DEBUG
                    errs() << op << " = " << op1 << " <= " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::BAD_ICMP_PREDICATE: {
                    errs() << "encounter bad icmp predicate \n";
                    exit(-1);
                }
                default: {
                    errs() << "can not hold this situation " << ins_ptr->getPredicate() << "\n";
                    exit(-1);
                }
            }
        } else {
            errs() << "can not hold float cmp!\n";
            exit(-1);
        }
        return ret;
    }

    z3::expr InstructionParser::extract_constraints(const PHINode *ins_ptr) {
        errs() << "In PHI states\n";
        z3::expr ret = c.bool_val(true);
        return ret;
    }

    z3::expr InstructionParser::extract_constraints(const BinaryOperator *ins_ptr) {
        const auto op1 = parse_llvm_value_to_string(ins_ptr->getOperand(0));
        const auto op2 = parse_llvm_value_to_string(ins_ptr->getOperand(1));
        const auto op = ins_ptr->getName();
        auto res = get_int_expr(op, true);
        auto num1 = get_int_expr(ins_ptr->getOperand(0));
        auto num2 = get_int_expr(ins_ptr->getOperand(1));
        auto ret = c.bool_val(true);
        switch (ins_ptr->getOpcode()) {
            case Instruction::Add: {
                ret = (res == num1 + num2);
#ifdef DEBUG
                errs() << op << " = " << op1 << " + " << op2 << " op expr: ";
                errs() << ret.to_string() << "\n";
#endif
                break;
            }
            case Instruction::Sub: {
                ret = (res == num1 - num2);
#ifdef DEBUG
                errs() << op << " = " << op1 << " - " << op2 << " op expr: ";
                errs() << ret.to_string() << "\n";
#endif
                break;
            }
            case Instruction::Mul: {
                ret = (res == num1 * num2);
#ifdef DEBUG
                errs() << op << " = " << op1 << " * " << op2 << " op expr: ";
                errs() << ret.to_string() << "\n";
#endif
                break;
            }
            case Instruction::SDiv: {
                ret = (res == num1 / num2);
#ifdef DEBUG
                errs() << op << " = " << op1 << " / " << op2 << " op expr: ";
                errs() << ret.to_string() << "\n";
#endif
                break;
            }
            default: {
                errs() << "UnKnown operation" << "\n";
                exit(-1);
            }
        }
        return z3::expr(c);
    }

    z3::expr InstructionParser::extract_constraints(const AllocaInst *ins_ptr) {
        z3::expr ret = c.bool_val(true);
        return ret;
    }

    // CQ: how to deal with branch
    z3::expr InstructionParser::extract_constraints(const BranchInst *ins_ptr, std::string& branch_name) {
        z3::expr ret = c.bool_val(true);
        if (ins_ptr->isConditional()) {
            auto br_name = parse_llvm_value_to_string(ins_ptr->getOperand(0));
            auto true_branch = ins_ptr->getSuccessor(0)->getName();
            auto false_branch = ins_ptr->getSuccessor(1)->getName();
            auto br_indexed_name = get_indexed_name(br_name);
            auto e = c.bool_const(br_indexed_name.c_str());
#ifdef DEBUG
            if (branch_name == true_branch) {
                ret = e;
            } else {
                ret = !e;
            }
            errs() << "if (" << br_name << ") -> " << true_branch << " else -> " << false_branch << "\n";
#endif
        } else {
#ifdef DEBUG
            errs() << "In branch: " << parse_llvm_value_to_string(ins_ptr->getOperand(0)) << "\n";
#endif
        }
        return ret;
    }


    z3::expr InstructionParser::extract_constraints(const ReturnInst *ins_ptr) {
        auto ret_val = parse_llvm_value_to_string(ins_ptr->getOperand(0));
#ifdef DEBUG
        errs() << "return: " << ret_val << "\n";
#endif
        z3::expr ret = c.bool_val(true);
        return ret;
    }

    void InstructionParser::print_z3_model(z3::model &mod) {
        for (int i = 0; i < mod.size(); i++) {
            z3::func_decl v = mod[i];
            assert(v.arity() == 0);
            std::cout << v.name() << " = " << mod.get_const_interp(v) << "\n";
        }
    }

    std::string InstructionParser::parse_llvm_value_to_string(const Value *val) {
        std::string ret;
        if (val->hasName()) {
            ret = val->getName();
        } else {
            if (const auto *CI = dyn_cast<ConstantInt>(val)) {
                int int_val = CI->getSExtValue();
                ret = std::to_string(int_val);
            } else if (const auto *CFP = dyn_cast<ConstantFP>(val)) {
                double double_val = CFP->getValueAPF().convertToDouble();
                ret = std::to_string(double_val);
            } else {
                errs() << "can not parse_single to string of value " << *val << "\n";
                std::cout << "Unknown value type" << std::endl;
                exit(-1);
            }
        }
        return ret;
    }

    bool InstructionParser::is_real_value(const Value *val) {
        if (dyn_cast<ConstantInt>(val) || dyn_cast<ConstantFP>(val)) {
            return true;
        }
        return false;
    }

    std::tuple<int, int, double> InstructionParser::get_real_value(const Value *val) {
        if (const auto *CI = dyn_cast<ConstantInt>(val)) {
            int int_val = CI->getSExtValue();
            return std::tuple<int, int, double>(INT, int_val, 0);
        } else if (const auto *CFP = dyn_cast<ConstantFP>(val)) {
            double double_val = CFP->getValueAPF().convertToDouble();
            return std::tuple<int, int, double>(DOUBLE, 0, double_val);
        }
        return std::tuple<int, int, double>(UNKNOWN, 0, 0);
    }

    z3::expr InstructionParser::get_int_expr(const Value *val, bool is_left_value) {
        z3::expr e(c);
        if (is_real_value(val)) {
            auto payload = get_real_value(val);
            if (std::get<0>(payload) == INT) {
                int real_val = std::get<INT>(payload);
                e = c.int_val(real_val);
            } else if (std::get<0>(payload) == DOUBLE) {
                double real_val = std::get<DOUBLE>(payload);
                errs() << "can not calculate float value\n";
                exit(-1);
            }
        } else {
            std::string name = parse_llvm_value_to_string(val);
            return get_int_expr(name, is_left_value);
        }
        return e;
    }

    z3::expr InstructionParser::get_int_expr(const StringRef &s, bool is_left_value) {
        std::string str = s;
        return get_int_expr(str, is_left_value);
    }

    int InstructionParser::get_index(const std::string &name, bool is_left_value) {
        if (is_left_value) {
            if (index.count(name)) {
                return ++ index[name];
            }
            return index[name] = 0;
        } else {
            return index[name];
        }
    }

    z3::expr InstructionParser::get_int_expr(const std::string& s, bool is_left_value) {
        auto name = get_indexed_name(s, is_left_value);
        return c.int_const(name.c_str());
    }

    std::string InstructionParser::get_indexed_name(const std::string &s, bool is_left_value) {
        auto name = std::to_string(get_index(s, is_left_value)) + "_" + s;
        return name;
    }

}