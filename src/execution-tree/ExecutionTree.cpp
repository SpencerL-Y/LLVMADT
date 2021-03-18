//
// Created by center on 2021/3/13.
//

#include "../../include/execution-tree/ExecutionTree.h"
#include "../../include/execution-tree/InstructionParser.h"
namespace sym_exe {
    ExecutionTree::ExecutionTree() {
        roots.clear();
    }

    void ExecutionTree::build_tree(Module& module) {
        for (auto& function : module) {
            auto ptr = std::make_shared<Node>();
            ptr->add_son(function);
            roots[function.getName()] = ptr;
        }
    }

    void ExecutionTree::print_names() {
        for (auto& i : roots) {
            std::cout << i.first << std::endl;
        }
    }

    void ExecutionTree::print_tree(std::string& func_name) {
        if (roots.count(func_name)) {
            print_tree(roots[func_name]);
            return;
        }
        std::cout << "Invalid function name: " << func_name << std::endl;
    }

    void ExecutionTree::print_all_trees() {
        for (auto& i : roots) {
            std::cout << "Printing function tree: " << i.first << std::endl;
            print_tree(i.second);
        }
    }

    void ExecutionTree::print_tree(NodePtr& node_ptr) {
        static std::vector<std::string> instructions;
        instructions.push_back(node_ptr->get_string_info());
        if (node_ptr->empty()) {
            for(auto &i : instructions) {
                std::cout << i;
            }
            std::cout << std::endl;
            return;
        }
        auto& v = node_ptr->get_son();
        for (auto &i : v) {
            std::string str = "In BB: " + i.first + "\n";
            instructions.push_back(str);
            print_tree(i.second);
            instructions.pop_back();
            instructions.pop_back();
        }
    }

    void ExecutionTree::do_execution_test(NodePtr &node_ptr) {
        static std::vector<InsPtr> instructions;
        static std::vector<std::string> branch_name;
        auto vec = node_ptr->get_states().get_instruction_ptr_vec();
        instructions.reserve(vec.size());
        for (auto t : vec) {
            instructions.push_back(t);
        }
        if (node_ptr->empty()) {
            InstructionParser parser;
            parser.solve(instructions, branch_name);
            return;
        }
        auto& v = node_ptr->get_son();
        for (auto &i : v) {
            auto num = i.second->get_states().get_instruction_ptr_vec().size();
            branch_name.push_back(i.first);
            do_execution_test(i.second);
            while (num --) {
                instructions.pop_back();
            }
            branch_name.pop_back();
        }
    }

    std::unordered_map<std::string, NodePtr> &ExecutionTree::get_roots() {
        return roots;
    }

    NodePtr ExecutionTree::get_roots(const std::string& name) {
        return roots[name];
    }
}