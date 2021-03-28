#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include "../include/execution-tree/ExecutionNode.h"
#include "../include/execution-tree/ExecutionTree.h"
#include "z3++.h"
#include "../include/execution-tree/InstructionParser.h"
#include "execution-tree/TableBuilder.h"
using namespace z3;
using namespace std;
using namespace sym_exe;

void find_model_example1() {
    std::cout << "find_model_example1\n";
    context c;
    expr x = c.int_const("x");
    expr y = c.int_const("y");
    expr a = c.int_const("a");
    expr b = c.int_const("b");
    expr e = (x == 2 * (a + b) && y == 4 && a != 0 && b == 0 && !((x - y) != 0));
    solver s(c);
    s.push();
    s.add(e);
    s.check();
    auto t = s.get_model();
    cout << t.to_string() << endl;
    sym_exe::InstructionParser::print_z3_model(t);
    s.pop();
    s.add(x==1 && y < 3 && a + b < x * 2 + y);
    s.check();
    t = s.get_model();
    sym_exe::InstructionParser::print_z3_model(t);
}

void find_model_example() {
    context c;
    expr retval = c.int_const("retval");
    expr x0 = c.int_const("x0");
    expr y0 = c.int_const("y0");
    expr tmp0 = c.int_const("tmp0");
    expr cmp0 = c.bool_const("cmp0");
    expr tmp10 = c.int_const("tmp10");
    expr add0 = c.int_const("add0");
    expr y1 = c.int_const("y1");
    expr tmp20 = c.int_const("cmp20");
    expr b0 = c.int_const("b0");
    expr cmp10 = c.bool_const("cmp10");
    expr tmp50 = c.int_const("tmp50");
    expr tmp60 = c.int_const("tmp60");
    expr sub0 = c.int_const("sub0");
    expr cmp40 = c.bool_const("cmp40");
    expr a0 = c.int_const("a0");

    vector<expr> v;
// not ok
//    v.push_back(retval == 0);
//    v.push_back(x0 == 1);
//    v.push_back(y0 == 0);
//    v.push_back(tmp0 == a0);
//    v.push_back(cmp0 == (tmp0 != 0));
//    v.push_back(cmp0);
//    v.push_back(tmp10 == x0);
//    v.push_back(add0 == (3 + tmp10));
//    v.push_back(add0 == y1);
//    v.push_back(b0 == tmp20);
//    v.push_back(cmp10 == (tmp20 == 0));
//    v.push_back(not cmp10);
//    v.push_back(tmp50 == x0);
//    v.push_back(tmp60 == y1);
//    v.push_back(sub0 == (tmp50 - tmp60));
//    v.push_back(cmp40 == (sub0 != 0));
//    v.push_back(not cmp40);

    v.push_back(x0 == 1);
    v.push_back(a0 != 0);
    v.push_back(y1 == (3 + x0));
    v.push_back(b0 != 0);
    v.push_back((x0 - y1) == 0);
    solver solver(c);
    for (auto i : v) {
        solver.add(i);
        if (solver.check() != sat) {
            std::cout << "error in expr: " << i.to_string() << endl;
            return;
        }
        auto mod = solver.get_model();
        cout << "last expr " << i.to_string() << endl;
        sym_exe::InstructionParser::print_z3_model(mod);
        cout << endl;
    }
}

int symbolic_execution(int argc, char** argv) {
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
    tree.build_tree_with_loop(*mod);
#if DEBUG
    tree.print_names();
    tree.print_all_trees();
#endif
    std::string s = "main";
    auto node_ptr = tree.get_roots(s);
    tree.do_execution_test(node_ptr);
    return 0;
}

void test(int argc, char** argv) {
    llvm::LLVMContext context;
    llvm::SMDiagnostic err;
    if (argc <= 1) {
        std::cout << "Invalid path" << std::endl;
        return;
    }
    std::string ll_path = argv[1];
    std::unique_ptr<llvm::Module> Mod = parseIRFile(ll_path, err, context);
    llvm::Module* mod  = Mod.get();
    ExecutionTree tree;
    tree.build_tree_with_loop(*mod);
    tree.print_all_trees();
}

void test_pointer(int argc, char** argv) {
    llvm::LLVMContext context;
    llvm::SMDiagnostic err;
    if (argc <= 1) {
        std::cout << "Invalid path" << std::endl;
        return;
    }
    std::string ll_path = argv[1];
    std::unique_ptr<llvm::Module> Mod = parseIRFile(ll_path, err, context);
    llvm::Module* mod  = Mod.get();
    TableBuilder tableBuilder;
    for (auto& func : *mod) {
        if (func.empty()) continue;
        for (auto &bb : func) {
            for (auto& ins : bb) {
                tableBuilder.parse_single(&ins);
//                tableBuilder.get_table().print_table();
            }
        }
    }
    tableBuilder.get_table().print_table();
    tableBuilder.get_table().check_memory_leak();
}
int main(int argc, char** argv) {
//    find_model_example1();
//    find_model_example();
//    symbolic_execution(argc, argv);
//    test(argc, argv);
    test_pointer(argc, argv);
    return 0;
}