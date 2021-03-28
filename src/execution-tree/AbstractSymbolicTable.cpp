//
// Created by center on 2021/3/25.
//

#include <string>
#include <utility>
#include <cstdio>
#include "AbstractSymbolicTable.h"

using namespace std;
namespace sym_exe {

    Payload::Payload(string var_name, string value, bool auto_generated, int abstract_address) : var_name(
            std::move(var_name)), abstract_address(abstract_address), auto_generate(auto_generated), value(value) {
        up_bound = down_bound = 0;
    }

    void Payload::set_bound(int u, int d) {
        up_bound = u;
        down_bound = d;
    }

    void Payload::set_name(string name) {
        var_name = std::move(name);
    }

    void Payload::set_value(string name) {
        value = std::move(name);
    }

    AbstractSymbolicTable::AbstractSymbolicTable() {
        table.emplace_back("nullptr", "U", true, 0);
    }

    void AbstractSymbolicTable::add_data(Payload &payload) {
        int sz = table.size();
        payload.abstract_address = sz;
        table.emplace_back(payload);
        abstract_address[payload.var_name] = sz;
    }

    void AbstractSymbolicTable::check_memory_leak() {

    }

    void AbstractSymbolicTable::print_table() {
        printf("%-15s%-15s%-15s%-15s\n", "address", "var_name", "value", "autonerated");
        for (auto& i : table) {
            printf("%-15d%-15s%-15s%-15d\n", i.abstract_address, i.var_name.c_str(), i.value.c_str(), i.auto_generate);
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

}