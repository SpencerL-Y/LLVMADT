//
// Created by center on 2021/3/12.
//
#pragma once
#ifndef LLVMADT_EXECSTATE_H
#define LLVMADT_EXECSTATE_H
#include <llvm/IR/Instruction.h>
#include "myTranslate.hpp"
#include "llvm/IR/BasicBlock.h"

namespace sym_exe {
    typedef llvm::Instruction Ins;
    typedef Ins* InsPtr;

    class ExecState {
        typedef llvm::BasicBlock* BBPtr;
    public:
        explicit ExecState();

        void add_instruction(InsPtr insPtr);

        [[nodiscard]] std::string to_string() const;

        std::vector<InsPtr>& get_instruction_ptr_vec();

        void extract_info(BBPtr bb_ptr);

        static std::string to_string(InsPtr ins_ptr);

        void set_block_name(std::string name);
        std::string get_block_name() const;

    private:
        std::vector<z3::expr*> constraints_vec;
        std::vector<InsPtr> instruction_ptr_vec;
        std::string block_name;
    };
}
#endif //LLVMADT_EXECSTATE_H
