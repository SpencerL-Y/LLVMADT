//
// Created by center on 2021/3/14.
//

#include "../../include/execution-tree/InstructionParser.h"
#include "TableBuilder.h"

namespace sym_exe {

    const int InstructionParser::INT = 1;
    const int InstructionParser::DOUBLE = 2;
    const int InstructionParser::UNKNOWN = 3;


    void InstructionParser::parse_single(InsPtr ins_ptr) {
        errs() << *ins_ptr << "\n\t" << get_constraint(ins_ptr).to_string();
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
        if (const ReturnInst *returnInst = dyn_cast<ReturnInst>(ins_ptr)) {
            return extract_constraints(returnInst);
        }
        if (const AllocaInst *allocaInst = dyn_cast<AllocaInst>(ins_ptr)) {
            return extract_constraints(allocaInst);
        }
        if (const CallInst * callInst = dyn_cast<CallInst>(ins_ptr)) {
            return extract_constraints(callInst);
        }
        if (const UnreachableInst* unreachableInst = dyn_cast<UnreachableInst>(ins_ptr)) {
            extract_constraints(unreachableInst);
            return c.bool_val(true);
        }
        errs() << "Unknown statement : " << *ins_ptr <<"\n";
        return c.bool_val(true);
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
#if DEBUG
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
#if DEBUG
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
#if DEBUG
                    errs() << op << " = " << op1 << " = " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case llvm::CmpInst::ICMP_NE: {
                    ret = (res == (num1 != num2));
#if DEBUG
                    errs() << op << " = " << op1 << " != " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_UGT: {
                    ret = (res == (num1 >= num2));
#if DEBUG
                    errs() << op << " = " << op1 << " >= " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_UGE: {
                    ret = (res == (num1 != num2));
#if DEBUG
                    errs() << op << " = " << op1 << " != " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_ULT: {
                    ret = (res == (num1 < num2));
#if DEBUG
                    errs() << op << " = " << op1 << " < " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_ULE: {
                    ret = (res == (num1 <= num2));
#if DEBUG
                    errs() << op << " = " << op1 << " <= " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_SGT: {
                    ret = (res == (num1 > num2));
#if DEBUG
                    errs() << op << " = " << op1 << " > " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_SGE: {
                    ret = (res == (num1 >= num2));
#if DEBUG
                    errs() << op << " = " << op1 << " >= " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_SLT: {
                    ret = (res == (num1 < num2));
#if DEBUG
                    errs() << op << " = " << op1 << " < " << op2 << " cmp expr: ";
                    errs() << ret.to_string() << "\n";
#endif
                    break;
                }
                case CmpInst::ICMP_SLE: {
                    ret = (res == (num1 <= num2));
#if DEBUG
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
#if DEBUG
                errs() << op << " = " << op1 << " + " << op2 << " op expr: ";
                errs() << ret.to_string() << "\n";
#endif
                break;
            }
            case Instruction::Sub: {
                ret = (res == num1 - num2);
#if DEBUG
                errs() << op << " = " << op1 << " - " << op2 << " op expr: ";
                errs() << ret.to_string() << "\n";
#endif
                break;
            }
            case Instruction::Mul: {
                ret = (res == num1 * num2);
#if DEBUG
                errs() << op << " = " << op1 << " * " << op2 << " op expr: ";
                errs() << ret.to_string() << "\n";
#endif
                break;
            }
            case Instruction::SDiv: {
                ret = (res == num1 / num2);
#if DEBUG
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
        return ret;
    }

    z3::expr InstructionParser::extract_constraints(const AllocaInst *ins_ptr) {
        z3::expr ret = c.bool_val(true);
        undefined_var[get_indexed_name(ins_ptr->getName())] = "random value";
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
            if (branch_name == true_branch) {
                ret = e;
            } else if (branch_name == false_branch){
                ret = !e;
            } else {
                errs() << "Branch name not match!\n";
                exit(1);
            }
#if DEBUG
            errs() << "if (" << br_name << ") -> " << true_branch << " else -> " << false_branch << "\n";
#endif
        } else {
#if DEBUG
            errs() << "In branch: " << parse_llvm_value_to_string(ins_ptr->getOperand(0)) << "\n";
#endif
        }
        return ret;
    }


    z3::expr InstructionParser::extract_constraints(const ReturnInst *ins_ptr) {
        auto ret_val = parse_llvm_value_to_string(ins_ptr->getOperand(0));
#if DEBUG
        errs() << "return: " << ret_val << "\n";
#endif
        auto return_name = ins_ptr->getOperand(0)->getName();
        if (!return_name.empty()) {
#if DEBUG
            errs() << "return var: " << get_indexed_name(return_name) << "\n";
#endif
            return_var[get_indexed_name(return_name)] = "random value";
        } else {
            return_var["return"] = ret_val;
        }
        z3::expr ret = c.bool_val(true);
        return ret;
    }

    z3::expr InstructionParser::extract_constraints(const CallInst *ins_ptr) {
        auto func = ins_ptr->getCalledFunction();
        if (func) {
            auto str = func->getName();
            if (str == "__isoc99_scanf") {
                for (auto op = ins_ptr->op_begin(); op != ins_ptr->op_end(); ++ op) {
                    if (op == ins_ptr->op_end() - 1) {
                        break;
                    }
                    // don't know why, the first value is empty
                    if (op == ins_ptr->op_begin()) {
                        continue;
                    }
                    auto v = op->get();
#if DEBUG
                    int n = 1;
                    errs() << n ++ << ": " << v->getName() << " " << get_indexed_name(v->getName()) << "\n";
#endif
                    input_var[get_indexed_name(v->getName())] = "random value";
                    undefined_var.erase(get_indexed_name(v->getName()));
                }
            }
        }
#if DEBUG
        errs() << ins_ptr->getCalledValue()->stripPointerCasts()->getName() << "\t";
#endif

        return c.bool_val(true);
    }

    void InstructionParser::print_z3_model(z3::model &mod) {
        for (int i = 0; i < mod.size(); i++) {
            z3::func_decl v = mod[i];
            assert(v.arity() == 0);
            std::cout << v.name().str() << " = " << mod.get_const_interp(v) << "\n";
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
//            if (index.count(name)) {
//                return index[name];
//            }
            return index[name];
        }
    }

    z3::expr InstructionParser::get_int_expr(const std::string& s, bool is_left_value) {
        auto name = get_indexed_name(s, is_left_value);
        if (is_left_value) {
            undefined_var.erase(name);
        }
        return c.int_const(name.c_str());
    }

    std::string InstructionParser::get_indexed_name(const std::string &s, bool is_left_value) {
        auto name = std::to_string(get_index(s, is_left_value)) + "_" + s;
        return name;
    }

    bool InstructionParser::solve(std::vector<InsPtr> &ins_vec, std::vector<std::string> &branch_vec) {
#if DEBUG
        int n = 1;
        for (auto& i : ins_vec) {
            llvm::errs() << *i << "\n";
            if (llvm::dyn_cast<llvm::BranchInst>(i)) {
                llvm::errs() << "(to branch " << branch_vec[n ++] << ") " << *i << " ";
            }
        }
        llvm::errs() << "\n";
#endif
        error_ptr = make_shared<ErrorManager>();
        z3::expr final = c.bool_val("true");
        TableBuilder tableBuilder;
        tableBuilder.set_error_manager(error_ptr);
        int pos = 1;
        for (auto &i : ins_vec) {
            z3::expr e = c.bool_val(true);
            tableBuilder.parse_single(i);
            check_errors(i, final);
            if (const auto ins_ptr = dyn_cast<BranchInst>(i)) {
                e = extract_constraints(ins_ptr, branch_vec[pos ++]);
            } else {
                e = get_constraint(i);
            }
            final = final & e;
#if DEBUG
            std::cout << ExecState::to_string(i) << "\t" << e.to_string() << std::endl;
#endif
        }
        z3::solver solver(c);
        std::cout << final.to_string() << std::endl;
        solver.add(final);
        if (solver.check() == z3::unsat) {
            pos = 0;
            std::cout << "\033[33mexecution path\n\t" << branch_vec[pos ++];
            while (pos < branch_vec.size()) {
                std::cout << " -> " << branch_vec[pos ++];
            }
            std::cout << "\nOK, unreachable path\033[0m" << std::endl;
            return false;
        }

        tableBuilder.get_table().print_table();
        tableBuilder.get_table().check();

        auto model = solver.get_model();
#if DEBUG
        print_z3_model(model);
#endif
        get_model_info(model);

        for (auto &i : return_var) {
            if (i.second != "0") {
                error_ptr->add_error("return non zero", "return " + i.second);
            }
        }
        if (return_var.empty()) {
            error_ptr->add_error("return nothing", "return value is empty");
        }
        // print result
        if (!error_ptr->have_error()) {
            pos = 0;
            std::cout << "\033[92mOK, this path is fine:\nexecution path\n\t" << branch_vec[pos ++];
            while (pos < branch_vec.size()) {
                std::cout << " -> " << branch_vec[pos ++];
            }
            std::cout << "\n";
            print_var_info();
            std::cout <<"\033[0m" << std::endl;
        } else {
            pos = 0;
            std::cout << "\033[91mCounter errors! This path is BAD!\nexecution path\n\t" << branch_vec[pos ++];
            while (pos < branch_vec.size()) {
                std::cout << " -> " << branch_vec[pos ++];
            }
            std::cout << "\n";
            print_var_info();
            std::cout <<"\033[0m" << std::endl;
            error_ptr->print_error();
        }
        return true;
    }



    void InstructionParser::extract_constraints(const UnreachableInst *unreachableInst) {
        errs() << "Counter unreachable IR \n";
    }

    std::string InstructionParser::get_origin_name(const std::string &s) {
        for (int i = 0; i < s.length(); ++ i) {
            if (s[i] == '_') {
                return s.substr(i + 1, s.length() - i);
            }
        }
        return s;
    }

    void InstructionParser::get_model_info(z3::model &mod) {
        for (int i = 0; i < mod.size(); i++) {
            z3::func_decl v = mod[i];
            assert(v.arity() == 0);
            auto name = v.name().str();
            if (input_var.count(name)) {
                input_var[name] = mod.get_const_interp(v).to_string();
            }
            if (return_var.count(name)) {
                return_var[name] = mod.get_const_interp(v).to_string();
            }
            if (undefined_var.count(name)) {
                undefined_var[name] = mod.get_const_interp(v).to_string();
            }
        }
    }

    std::unordered_map<std::string, std::string> &InstructionParser::get_input_var() {
        return input_var;
    }

    std::unordered_map<std::string, std::string> &InstructionParser::get_return_var() {
        return return_var;
    }

    void InstructionParser::check_errors(InsPtr &ins_ptr, z3::expr &now_constraints) {
        if (dyn_cast<BinaryOperator>(ins_ptr)) {
            if (ins_ptr->getOpcode()==Instruction::SDiv) {
                detect_divide_zero(ins_ptr, now_constraints);
            }
        }
    }

    void InstructionParser::detect_divide_zero(InsPtr ins_ptr, z3::expr &now_constraints) {
        auto op2 = ins_ptr->getOperand(1);
        auto num2 = get_int_expr(op2);
        z3::solver solver(c);
        solver.push();
        solver.add(now_constraints && (num2 == 0));
        string error_info;
        if (solver.check() == z3::sat) {
            is_ok = false;
            auto mod = solver.get_model();
            get_model_info(mod);
            error_info += "\033[91mMay cause divide zero error when input is: \n";
            for (auto &i : input_var) {
                error_info += "\t" + get_origin_name(i.first) + " = " + i.second + "\n";
            }
//            std::cout << "and uninitialized parameter:\n";
//            for (auto &i : undefined_var) {
//                std::cout << "\t" << get_origin_name(i.first) << " = " << i.second << std::endl;
//            }
            error_info += "related param name: " + op2->getName().str() + "\033[0m" + "\n";
        }
        error_ptr->add_error("divide zero error", error_info);
        solver.pop();
    }


    void InstructionParser::print_input_var() {
        if (!input_var.empty()) {
            std::cout << "input val: \n";
            for (auto &i : input_var) {
                std::cout << "\t" << get_origin_name(i.first) << " = " << i.second << std::endl;
            }
        }
    }

    void InstructionParser::print_return_var() {
        if (!return_var.empty()) {
            std::cout << "return val: \n";
            for (auto &i : return_var) {
                std::cout << "\t" << get_origin_name(i.first) << " = " << i.second << std::endl;
            }
        }
    }

    void InstructionParser::print_undefined_var() {
        if (!undefined_var.empty()) {
            std::cout << "undefined var: \n";
            for (auto &i : undefined_var) {
                std::cout << "\t" << get_origin_name(i.first) << " = " << i.second << std::endl;
            }
        }
    }

    void InstructionParser::print_var_info() {
        print_input_var();
        print_return_var();
        print_undefined_var();
    }

    void InstructionParser::set_error_manager_ptr(shared_ptr<ErrorManager>& em_ptr) {
        error_ptr = em_ptr;
    }

}