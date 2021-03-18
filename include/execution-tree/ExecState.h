//
// Created by center on 2021/3/12.
//
#pragma once
#ifndef LLVMADT_EXECSTATE_H
#define LLVMADT_EXECSTATE_H
#include <llvm/IR/Instruction.h>
#include "myTranslate.hpp"


namespace sym_exe {
    typedef llvm::Instruction Ins;
    typedef Ins* InsPtr;

    class ExecState {
    public:
        explicit ExecState();

        void add_instruction(InsPtr insPtr);

        [[nodiscard]] std::string to_string() const;

        std::vector<InsPtr>& get_instruction_ptr_vec();

    private:
        std::vector<z3::expr*> constraints_vec;
        std::vector<InsPtr> instruction_ptr_vec;
    };
}
#endif //LLVMADT_EXECSTATE_H
