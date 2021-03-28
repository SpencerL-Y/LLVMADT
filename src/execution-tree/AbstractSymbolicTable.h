//
// Created by center on 2021/3/25.
//

#ifndef LLVMADT_ABSTRACTSYMBOLICTABLE_H
#define LLVMADT_ABSTRACTSYMBOLICTABLE_H
#pragma once

#include <vector>
#include <string>
#include <unordered_map>

using namespace std;

namespace sym_exe {
    struct Payload {
        string var_name;
        int abstract_address;
        bool auto_generate;
        string value;
        int up_bound;
        int down_bound;
        explicit Payload(string var_name = "Unknown", string value = "U", bool auto_generated = true, int abstract_address = 0);
        void set_bound(int up_bound, int down_bound);
        void set_name(string name);
        void set_value(string value);
    };

    class AbstractSymbolicTable {
    public:
        AbstractSymbolicTable();

        void add_data(Payload &payload);

        void check_memory_leak();

        void print_table();

        int get_size();

        int get_address(string& s, int dereference_time);

        int get_address(int ab_address, int dereference_time);

        string& get_value(int abstract_address);

        string& get_value(string& name, int dereference_time = 0);

        int count(string s);
    private:
        vector<Payload> table;
        unordered_map<string, int> abstract_address;
    };

}

#endif //LLVMADT_ABSTRACTSYMBOLICTABLE_H
