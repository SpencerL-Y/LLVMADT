#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include "../include/execution-tree/ExecutionNode.h"
#include "../include/execution-tree/ExecutionTree.h"
#include "z3++.h"
#include "../include/execution-tree/InstructionParser.h"
using namespace z3;
using namespace std;

void find_model_example1() {
    std::cout << "find_model_example1\n";
    context c;
    expr x = c.int_const("0_x");
    expr y = c.int_const("y");
    expr t_x = c.int_const("0_x");
    expr e = (t_x == 1 && y == 4 && (x + y > 2));
    std::cout << e << std::endl;
    solver s(c);
    s.add(e);
    s.check();
    auto t = s.get_model();
    cout << t.to_string() << endl;
    sym_exe::InstructionParser::print_z3_model(t);
}

void expr_example() {
    context c;
    context a;
    expr x = c.int_const("x");
    expr y = c.int_const("123");
    expr e = x + y > 3;
    solver s(c);
    expr z = e;
    
    s.add(z);
//    s.add(z == 3);
    cout << s.check() << endl;
    auto t = s.get_model();
    sym_exe::InstructionParser::print_z3_model(t);
}

int main(int argc, char** argv) {
    find_model_example1();
    llvm::LLVMContext context;
    llvm::SMDiagnostic err;
    if (argc <= 1) {
        std::cout << "Invalid path" << std::endl;
        return 0;
    }
    std::string ll_path = argv[1];
    std::unique_ptr<llvm::Module> Mod = parseIRFile(ll_path, err, context);
    llvm::Module* mod  = Mod.get();

    sym_exe::ExecutionTree tree;
    tree.build_tree(*mod);
    tree.print_names();
//    tree.print_all_trees();

    std::string s = "main";
    auto node_ptr = tree.get_roots(s);
    tree.do_execution_test(node_ptr);

//    z3::context c;
//    sym_exe::InstructionParser instructionParser;
//    for (auto &bb : *mod) {
//        for (auto& func : bb) {
//            for (auto &ins : func) {
//                instructionParser.parse_single(&ins);
//            }
//        }
//    }

    return 0;
}