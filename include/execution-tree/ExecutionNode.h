//
// Created by center on 2021/3/13.
//

#ifndef LLVMADT_EXECUTIONNODE_H
#define LLVMADT_EXECUTIONNODE_H

#include "ExecState.h"
#include <llvm/IR/Module.h>
#include <llvm/IR/Function.h>
#include <llvm/IR/BasicBlock.h>
#define DEBUG 0

namespace sym_exe{
    typedef llvm::Module Module;
    typedef Module* ModulePtr;
    typedef llvm::Function Func;
    typedef Func* FuncPtr;
    typedef llvm::BasicBlock BB;
    typedef BB* BBPtr;

    class ExecutionNode {
    public:
        typedef ExecutionNode Node;
        typedef std::shared_ptr<Node> NodePtr;

        explicit ExecutionNode() = default;
        explicit ExecutionNode(ExecState& exe_state);
        ExecutionNode(ExecState& exe_stater, std::unordered_map<std::string, NodePtr>& sons);

        void set_state(ExecState& state_);

        void add_son(Func& func);
        void add_son(FuncPtr func_ptr);
        NodePtr add_son(BB& bb);
        NodePtr add_son(BBPtr bb_ptr);
        void recursion_add_son(BB& bb);
        void recursion_add_son(BBPtr bb_ptr);

        bool empty();
        ExecState get_states();
        std::string get_string_info();
        std::unordered_map<std::string, NodePtr>& get_son();

    private:
        ExecState state;
//        std::vector<NodePtr> son;
        std::unordered_map<std::string, NodePtr> son;
    };
}



#endif //LLVMADT_EXECUTIONNODE_H
