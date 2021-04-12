//
// Created by center on 2021/3/25.
//

#ifndef LLVMADT_ABSTRACTSYMBOLICTABLE_H
#define LLVMADT_ABSTRACTSYMBOLICTABLE_H
#pragma once

#include <vector>
#include <string>
#include <unordered_map>
#include <memory>
#include "ErrorManager.h"
using namespace std;

namespace sym_exe {
    struct Payload {
        string var_name;
        int abstract_address;
        bool auto_free;
        string value;
        int _lower_bound;
        int _upper_bound;
        explicit Payload(string var_name = "Unknown", string value = "U", bool auto_generated = true, int abstract_address = 0);
        void set_bound(int lower_bound, int upper_bound);
        void set_name(string name);
        void set_value(string value);
        int get_lower_bound();
        int get_upper_bound();
    };

    class AbstractSymbolicTable {
    public:
        AbstractSymbolicTable();

        void add_data(Payload &payload);

        bool check_memory_leak();

        void print_table();

        int get_size();

        int get_address(string& s, int dereference_time);

        int get_address(int ab_address, int dereference_time);

        string& get_value(int abstract_address);

        string& get_value(string& name, int dereference_time = 0);

        int count(string s);

        Payload get_data(int pos);

        bool check_out_bound(string& pointer_name, int offset);

        void malloc(string& pointer_name, int block_num, bool auto_free = false);

        void free(string pointer_name);

        void set_error_manager(shared_ptr<ErrorManager>& error_manager);

        void check();
    private:
        vector<Payload> table;
        unordered_map<string, int> abstract_address;
        int unknown_num;
        shared_ptr<ErrorManager> error_ptr;
    };

}

#endif //LLVMADT_ABSTRACTSYMBOLICTABLE_H
