//
// Created by center on 2021/3/25.
//
#pragma once
#ifndef LLVMADT_TABLEBUILDER_H
#define LLVMADT_TABLEBUILDER_H
#include "AbstractSymbolicTable.h"
#include "../../include/execution-tree/ExecutionTree.h"

using namespace llvm;
namespace sym_exe {
    struct point_to_node {
        vector<string> son;
        string father;
    };
    class TableBuilder {
        typedef llvm::Instruction* InsPtr;
    public:
        void parse_single(InsPtr ins_ptr);
        AbstractSymbolicTable& get_table();
    private:
        AbstractSymbolicTable table;
        unordered_map<string, point_to_node> pointer_map;
        unordered_map<string, unsigned long long> malloc_info;

        void get_info(InsPtr ins_ptr);
        void extract_info(const AllocaInst *ins_ptr);
        void extract_info(const LoadInst *ins_ptr);
        void extract_info(const StoreInst* ins_ptr);
        void extract_info(const CallInst* ins_ptr);
        void extract_info(const BitCastInst* ins_ptr);
        void extract_info(const GetElementPtrInst* ins_ptr);
        static int get_pointer_level(const Value* value);
        string get_related_var(string& s);
        void add_pointer_son(string& father, string& son);
    };
}

#endif //LLVMADT_TABLEBUILDER_H
