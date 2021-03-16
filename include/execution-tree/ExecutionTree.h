//
// Created by center on 2021/3/13.
//

#ifndef LLVMADT_EXECUTIONTREE_H
#define LLVMADT_EXECUTIONTREE_H
#include <iostream>
#include "unordered_map"
#include "ExecutionNode.h"

namespace sym_exe {
    typedef ExecutionNode Node;
    typedef std::shared_ptr<Node> NodePtr;
    class ExecutionTree {
    public:
        ExecutionTree();

        void build_tree(Module& module);

        void print_names();

        void print_tree(NodePtr& node_ptr);

        void print_tree(std::string& func_name);

        void print_all_trees();

        void do_execution_test(NodePtr & node_ptr);

        std::unordered_map<std::string, NodePtr>& get_roots();

        NodePtr get_roots(const std::string& name);

    private:
        std::unordered_map<std::string, NodePtr> roots;

    };
}


#endif //LLVMADT_EXECUTIONTREE_H
