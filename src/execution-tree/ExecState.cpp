//
// Created by center on 2021/3/12.
//

#include "../../include/execution-tree/ExecState.h"
#include <llvm/Support/raw_ostream.h>

#include <utility>

namespace sym_exe {

    std::string ExecState::to_string() const {
        if (instruction_ptr_vec.empty()) {
            return "";
        }
        std::string str;
        str += get_block_name() + "\n";
        for (auto &instruction_ptr: instruction_ptr_vec) {
            llvm::raw_string_ostream(str) << *instruction_ptr << "\n";
        }
        return str;
    }

    void ExecState::add_instruction(InsPtr insPtr) {
        instruction_ptr_vec.push_back(insPtr);
    }

    ExecState::ExecState() {
        instruction_ptr_vec.clear();
        constraints_vec.clear();
        block_name = "Unknown";
    }

    std::vector<InsPtr> &ExecState::get_instruction_ptr_vec() {
        return instruction_ptr_vec;
    }

    std::string ExecState::to_string(InsPtr ins_ptr) {
        std::string str;
        llvm::raw_string_ostream(str) << *ins_ptr << "\n";
        return str;
    }

    void ExecState::extract_info(ExecState::BBPtr bb_ptr) {
        for (auto&i : *bb_ptr) {
            add_instruction(&i);
        }
        set_block_name(bb_ptr->getName());
    }

    void ExecState::set_block_name(std::string name) {
        block_name = std::move(name);
    }

    std::string ExecState::get_block_name() const {
        return block_name;
    }

}