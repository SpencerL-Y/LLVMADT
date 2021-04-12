//
// Created by center on 2021/4/12.
//

#include "ErrorManager.h"

#include <utility>

bool sym_exe::ErrorManager::have_error() {
    return has_error;
}

void sym_exe::ErrorManager::add_error(string error_name, string error_info) {
    has_error = true;
    errors[error_name] = std::move(error_info);
}

void sym_exe::ErrorManager::print_error() {
    for (auto &i : errors) {
        cout << "\033[91mError: " << i.first << endl;
        cout << "Info: " << i.second << "\033[0m" << endl;
    }
}

sym_exe::ErrorManager::ErrorManager() {
    has_error = false;
}
