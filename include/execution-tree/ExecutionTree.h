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

        void print(BBPtr bb_ptr);

        int get_loop_time() const;

        void build_tree(BBPtr bb_ptr, const NodePtr& node_ptr);

        void build_tree_with_loop(Module& module);

    private:
        std::unordered_map<std::string, NodePtr> roots;
        std::unordered_map<std::string, int> visited_num;
        int loop_time;
    };
}


#endif //LLVMADT_EXECUTIONTREE_H
