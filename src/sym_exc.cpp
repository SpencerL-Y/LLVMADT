#include <iostream>
#include <llvm/IR/LLVMContext.h>
#include <Converter.hpp>
#include "../include/execution-tree/ExecutionNode.h"
#include "../include/execution-tree/ExecutionTree.h"

int main(int argc, char** argv) {
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
    tree.print_all_trees();

    return 0;
}