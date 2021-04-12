//
// Created by center on 2021/3/14.
//
#pragma once
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

        void get_model_info(z3::model &mod);

        static std::string parse_llvm_value_to_string(const Value *val);

        z3::expr get_int_expr(const Value *val, bool is_left_value = false);

        z3::expr get_int_expr(const StringRef &s, bool is_left_value = false);

        z3::expr get_int_expr(const std::string& s, bool is_left_value = false);

        std::string get_indexed_name(const std::string& s, bool is_left_value = false);

        static std::string get_origin_name(const std::string& s);

        bool solve(std::vector<InsPtr>& ins_vec, std::vector<std::string>& branch_vec);

        std::unordered_map<std::string, std::string>& get_input_var();

        std::unordered_map<std::string, std::string>& get_return_var();

        static std::tuple<int, int, double> get_real_value(const Value *val);

        // check llvm::Value is number or just a name
        static bool is_real_value(const Value *val);

        void print_input_var();
        void print_undefined_var();
        void print_return_var();
        void print_var_info();

        void set_error_manager_ptr(shared_ptr<ErrorManager>& em_ptr);

    private:
        bool is_ok = true;
        // z3 context
        z3::context c;
        // use to get variable index
        std::unordered_map<std::string, int> index;
        // input variables
        std::unordered_map<std::string, std::string> input_var;
        // return variables
        std::unordered_map<std::string, std::string> return_var;
        // undefined variables
        std::unordered_map<std::string, std::string> undefined_var;

        std::shared_ptr<ErrorManager> error_ptr;

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

        z3::expr extract_constraints(const CallInst* ins_ptr);

        // TODO: complete
        z3::expr extract_constraints(const BranchInst *ins_ptr, std::string& branch_name);

        static void extract_constraints(const UnreachableInst * unreachableInst);

        void check_errors(InsPtr& ins_ptr, z3::expr &now_constraints);

        void detect_divide_zero(InsPtr ins_ptr, z3::expr &now_constraints);


    };
}


#endif //LLVMADT_INSTRUCTIONPARSER_H
