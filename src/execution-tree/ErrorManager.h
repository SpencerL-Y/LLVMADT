//
// Created by center on 2021/4/12.
//

#ifndef LLVMADT_ERRORMANAGER_H
#define LLVMADT_ERRORMANAGER_H

#include <unordered_map>
#include "string"
#include "iostream"
using namespace std;
namespace sym_exe{
    class ErrorManager {
    private:
        bool has_error;
        unordered_map<string, string> errors;

    public:
        ErrorManager();
        bool have_error();
        void add_error(string error_name, string error_info);
        void print_error();
    };

}


#endif //LLVMADT_ERRORMANAGER_H
