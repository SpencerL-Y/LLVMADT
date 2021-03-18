//
// Created by center on 2021/3/13.
//

#include "../../include/execution-tree/ExecutionNode.h"
#include <iostream>
#include <llvm/IR/CFG.h>
#include <llvm/IR/LLVMContext.h>
#include <Converter.hpp>

namespace sym_exe {

    ExecutionNode::ExecutionNode(ExecState &exe_state, std::unordered_map<std::string, NodePtr> &sons) : state(exe_state),
                                                                                     son(sons) {}

    ExecutionNode::ExecutionNode(ExecState &exe_state) : state(exe_state){
        son.clear();
    }

    void ExecutionNode::set_state(ExecState& state_) {
        state = state_;
    }


    void ExecutionNode::add_son(Func &func) {
        if (func.empty()) {
            return;
        }
        recursion_add_son(func.getEntryBlock());
    }

    void ExecutionNode::add_son(FuncPtr func_ptr) {
        add_son(*func_ptr);
    }

    ExecutionNode::NodePtr ExecutionNode::add_son(BB &bb) {
        ExecState states;
        for (auto &instruction : bb) {
            states.add_instruction(&instruction);
        }
        std::shared_ptr<Node> son_ptr = std::make_shared<Node>(states);
        son[bb.getName()] = son_ptr;
        return son_ptr;
    }

    ExecutionNode::NodePtr ExecutionNode::add_son(BBPtr bb_ptr) {
        return add_son(*bb_ptr);
    }

    void ExecutionNode::recursion_add_son(BB &bb) {
        recursion_add_son(&bb);
    }

    void ExecutionNode::recursion_add_son(BBPtr bb_ptr) {
        auto last_ptr = add_son(bb_ptr);
        auto set = llvm::successors(bb_ptr);
        for (auto s_ptr: set) {
            last_ptr->recursion_add_son(s_ptr);
        }
    }

    bool ExecutionNode::empty() {
        return son.empty();
    }

    ExecState ExecutionNode::get_states() {
        return state;
    }

    std::string ExecutionNode::get_string_info() {
        return state.to_string();
    }

    std::unordered_map<std::string, std::shared_ptr<ExecutionNode>> &ExecutionNode::get_son() {
        return son;
    }

}