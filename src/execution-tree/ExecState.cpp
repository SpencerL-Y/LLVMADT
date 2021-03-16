//
// Created by center on 2021/3/12.
//

#include "../../include/execution-tree/ExecState.h"
#include <llvm/Support/raw_ostream.h>

namespace sym_exe {

    std::string ExecState::to_string() const {
        if (instruction_ptr_vec.empty()) {
            return "";
        }
        std::string str;
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
    }

    std::vector<InsPtr> &ExecState::get_instruction_ptr_vec() {
        return instruction_ptr_vec;
    }

}