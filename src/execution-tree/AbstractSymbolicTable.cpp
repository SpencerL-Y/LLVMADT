//
// Created by center on 2021/3/25.
//

#include <string>
#include <utility>
#include <cstdio>
#include "AbstractSymbolicTable.h"
#include "iostream"
#include "ErrorManager.h"
#include <unordered_set>

using namespace std;
namespace sym_exe {

    Payload::Payload(string var_name, string value, bool auto_generated, int abstract_address) : var_name(
            std::move(var_name)), abstract_address(abstract_address), auto_free(auto_generated), value(value) {
        _lower_bound = _upper_bound = -1;
    }

    void Payload::set_bound(int lower_bound, int upper_bound) {
        _lower_bound = lower_bound;
        _upper_bound = upper_bound;
    }

    void Payload::set_name(string name) {
        var_name = std::move(name);
    }

    void Payload::set_value(string name) {
        value = std::move(name);
    }

    int Payload::get_lower_bound() {
        return _lower_bound;
    }

    int Payload::get_upper_bound() {
        return _upper_bound;
    }

    AbstractSymbolicTable::AbstractSymbolicTable() {
        unknown_num = 0;
        table.emplace_back("nullptr", "U", true, 0);
    }

    void AbstractSymbolicTable::add_data(Payload &payload) {
        int sz = table.size();
        payload.abstract_address = sz;
        if (payload.var_name == "Unknown") {
            payload.var_name += to_string(unknown_num ++);
        }
        if (payload._lower_bound == payload._upper_bound && payload._lower_bound == -1) {
            payload.set_bound(sz, sz);
        }
        table.emplace_back(payload);
        abstract_address[payload.var_name] = sz;
    }

    bool AbstractSymbolicTable::check_memory_leak() {
        unordered_set<string> s;
        string info;
        for (auto& i : table) {
            if  (!i.auto_free) {
                info += "\t" + i.var_name + " was not free!\n";
                s.insert(to_string(i.abstract_address));
            }
        }
        if (s.size()) {
            error_ptr->add_error("memory leak", "\n" + info);
        }
//        cout << "related pointers: ";
//        for (auto& i : table) {
//            if (s.count(i.value)) {
//                cout << i.var_name << " ";
//            }
//        }
//        cout << endl;
        return true;
    }

    void AbstractSymbolicTable::print_table() {
        printf("%-15s%-15s%-15s%-15s%-15s%-15s\n", "address", "var_name", "value", "auto_free", "lower_bound", "upper_bound");
        for (auto& i : table) {
            printf("%-15d%-15s%-15s%-15d%-15d%-15d\n", i.abstract_address, i.var_name.c_str(), i.value.c_str(), i.auto_free, i._lower_bound, i._upper_bound);
        }
        puts("");
    }

    int AbstractSymbolicTable::get_size() {
        return table.size();
    }

    int AbstractSymbolicTable::get_address(string &s, int dereference_time) {
        int ab_address = abstract_address[s];
        return get_address(ab_address, dereference_time);
    }


    string& AbstractSymbolicTable::get_value(int ab_address) {
        return table[ab_address].value;
    }

    string& AbstractSymbolicTable::get_value(string &name, int dereference_time) {
        return get_value(get_address(name, dereference_time));
    }

    int AbstractSymbolicTable::get_address(int ab_address, int dereference_time) {
        if (!dereference_time){
            return ab_address;
        }
        int new_address = atoi(table[ab_address].value.c_str());
        return get_address(new_address, dereference_time - 1);
    }

    int AbstractSymbolicTable::count(string s) {
        return abstract_address.count(s);
    }

    bool AbstractSymbolicTable::check_out_bound(string &pointer_name, int offset) {
        auto addr = get_address(pointer_name, 1);
        auto p = addr + offset;
        if (p < table[addr].get_lower_bound() || p > table[addr].get_upper_bound()) {
            string s;
            s += "param " + pointer_name + " index out of range error found!\n";
            error_ptr->add_error("index out of range", s);
            return false;
        }
        return true;
    }

    Payload AbstractSymbolicTable::get_data(int pos) {
        return table[pos];
    }

    void AbstractSymbolicTable::free(string pointer_name) {
        int addr = get_address(pointer_name, 1);
        int lower_bound = table[addr].get_lower_bound();
        int upper_bound = table[addr].get_upper_bound();
        if (addr != lower_bound) {
            string s;
            s = "Error: free() Invalid pointer\n";
            error_ptr->add_error("invalid free", s);
        }
        for (int i = addr; i <= upper_bound; ++ i) {
            table[i].auto_free = true;
        }
    }

    void AbstractSymbolicTable::malloc(string &pointer_name, int block_num, bool auto_free) {
        int start_pos;
        for (int i = 0; i < block_num; ++ i) {
            if(!i) {
                start_pos = get_size();
            }
            Payload payload("Unknown", "U", auto_free);
            payload.set_bound(start_pos, start_pos + block_num - 1);
            add_data(payload);
        }
        Payload payload(pointer_name, to_string(start_pos));
        add_data(payload);
    }

    void AbstractSymbolicTable::set_error_manager(shared_ptr<ErrorManager> &error_manager) {
        error_ptr = error_manager;
    }

    void AbstractSymbolicTable::check() {
        check_memory_leak();
    }

}