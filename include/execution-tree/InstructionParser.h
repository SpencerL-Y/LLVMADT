//
// Created by center on 2021/3/14.
//

#ifndef LLVMADT_INSTRUCTIONPARSER_H
#define LLVMADT_INSTRUCTIONPARSER_H

#include "ExecutionTree.h"
#include "z3++.h"
#include <tuple>

using namespace llvm;

namespace sym_exe {
    class InstructionParser {
    public:
        static const int INT;
        static const int DOUBLE;
        static const int UNKNOWN;

        explicit InstructionParser() = default;

        void parse_single(InsPtr ins_ptr);

        static std::string get_var_name(InsPtr ins_ptr);

        z3::expr get_constraint(InsPtr ins_ptr);

        static void print_z3_model(z3::model &mod);

        static std::string parse_llvm_value_to_string(const Value *val);

        z3::expr get_int_expr(const Value *val, bool is_left_value = false);

        z3::expr get_int_expr(const StringRef &s, bool is_left_value = false);

        z3::expr get_int_expr(const std::string& s, bool is_left_value = false);

        std::string get_indexed_name(const std::string& s, bool is_left_value = false);

    private:
        z3::context c;

        std::unordered_map<std::string, int> index;

        int get_index(const std::string& name, bool is_left_value);

        // get variable name
        static std::string extract_name(const BranchInst *ins_ptr);

        static std::string extract_name(const AllocaInst *ins_ptr);

        static std::string extract_name(const StoreInst *ins_ptr);

        static std::string extract_name(const CmpInst *ins_ptr);

        static std::string extract_name(const LoadInst *ins_ptr);

        // extract constraints
        z3::expr extract_constraints(const StoreInst *ins_ptr);

        z3::expr extract_constraints(const LoadInst *ins_ptr);

        // TODO: complete
        z3::expr extract_constraints(const CmpInst *ins_ptr);

        // TODO: complete
        z3::expr extract_constraints(const PHINode *ins_ptr);

        // TODO: complete
        z3::expr extract_constraints(const AllocaInst *ins_ptr);

        z3::expr extract_constraints(const BinaryOperator *ins_ptr);

        z3::expr extract_constraints(const ReturnInst *ins_ptr);

        // TODO: complete
        z3::expr extract_constraints(const BranchInst *ins_ptr, std::string& branch_name);

        // check llvm::Value is number or just a name
        static bool is_real_value(const Value *val);

        static std::tuple<int, int, double> get_real_value(const Value *val);
    };
}


#endif //LLVMADT_INSTRUCTIONPARSER_H
