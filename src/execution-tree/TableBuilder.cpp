//
// Created by center on 2021/3/25.
//
#include "../../include/execution-tree/InstructionParser.h"
#include "TableBuilder.h"
using namespace llvm;
namespace sym_exe {

    void TableBuilder::parse_single(TableBuilder::InsPtr ins_ptr) {
//        errs() << *ins_ptr << "\n\t";
        get_info(ins_ptr);
//        errs() << "\n";
    }

    void TableBuilder::extract_info(const StoreInst *ins_ptr) {
        auto right = ins_ptr->getValueOperand();
        auto left = ins_ptr->getPointerOperand();
        string left_name = InstructionParser::parse_llvm_value_to_string(left);
        string right_name = InstructionParser::parse_llvm_value_to_string(right);
        if (InstructionParser::is_real_value(right)) {
            if (!table.count(left_name)) {
                errs() << "can not found variable " << left_name << "\n";
                exit(1);
            }
            auto& left_val = table.get_value(left_name, 1);
            left_val = right_name;

            if (table.get_address(left_name, 1) == 0) {
                cout << "Dereference error found!" << "\n";
                cout << "Related variables: " << get_related_var(left_name) << "\n";
            }

        } else {
            auto& right_val = table.get_value(right_name);
            auto& left_val = table.get_value(left_name, 1);
            left_val = right_val;

            add_pointer_son(left_name, right_name);
        }
#if DEBUG
        errs() << right_name<< " " <<get_pointer_level(right) << " " << table.get_value(right_name) <<"\n\t";
        errs() << left_name << " " << get_pointer_level(left) << " " << table.get_value(left_name, 1) << "\n";
#endif
    }

    void TableBuilder::extract_info(const LoadInst *ins_ptr) {
        auto right = ins_ptr->getPointerOperand();
        auto left = ins_ptr->getValueName()->getValue();
        string left_name = left->getName();
        string right_name = right->getName();
        int dereference_time = get_pointer_level(right) - get_pointer_level(left);
        if (!table.count(left_name)) {
            Payload payload(left_name);
            table.add_data(payload);
        }
        if (dereference_time) {
            add_pointer_son(right_name, left_name);
        }
        auto& right_val = table.get_value(right_name, dereference_time);
        auto& left_val = table.get_value(left_name);
        left_val = right_val;
#if DEBUG
        errs() << "here!!! " << left_val << " " << right_val << "\n\t";
        errs() << right_name<< " " << get_pointer_level(right) << " " << right_val   <<"\n\t";
        errs() << left_name << " " << get_pointer_level(left) <<  " " << left_val << "\n";
#endif
    }

    void TableBuilder::extract_info(const AllocaInst *ins_ptr) {
        auto op = ins_ptr->getValueName()->getValue();
#if DEBUG
        errs() << op->getName() << " " << get_pointer_level(op) << "\n";
        errs() << ins_ptr->getNumOperands() << "\n";
        errs() << ins_ptr->getType()->getElementType()->isArrayTy() << "\n";
        errs() << ins_ptr->getOperand(0)->getType()->isPointerTy() << "\n";
#endif
        // check if alloca an array
        if (ins_ptr->getType()->getElementType()->isArrayTy()) {
            int n = ins_ptr->getType()->getElementType()->getArrayNumElements();
            string name = op->getName();
            table.malloc(name, n, true);
        } else {
            auto level = get_pointer_level(ins_ptr);
            if (level) {
                Payload payload("Unknown", "U");
                if (level > 1) {
                    payload.set_value("0");
                }

                table.add_data(payload);
                Payload now(op->getName(),to_string(table.get_size() - 1));
                table.add_data(now);
            }
        }
    }

    void TableBuilder::get_info(TableBuilder::InsPtr ins_ptr) {
        if (const auto SI = dyn_cast<StoreInst>(ins_ptr)) {
            extract_info(SI);
        }
        if (const auto LI = dyn_cast<LoadInst>(ins_ptr)) {
            extract_info(LI);
        }
        if (const auto AI = dyn_cast<AllocaInst>(ins_ptr)) {
            extract_info(AI);
        }
        if (const auto CI = dyn_cast<CallInst>(ins_ptr)) {
            extract_info(CI);
        }
        if (const auto BC = dyn_cast<BitCastInst>(ins_ptr)) {
            extract_info(BC);
        }
        if (const auto GE = dyn_cast<GetElementPtrInst>(ins_ptr)) {
            extract_info(GE);
        }
    }

    int TableBuilder::get_pointer_level(const Value *value) {
        int pointer_level = 0;
        auto type = value->getType();
        if (type->isPointerTy()) {
            while(type->getNumContainedTypes()) {
                pointer_level ++;
                type = type->getContainedType(0);
            }
        }
        return pointer_level;
    }

    AbstractSymbolicTable &TableBuilder::get_table() {
        return table;
    }

    string TableBuilder::get_related_var(string &s) {
        static vector<string> v;
        v.push_back(s);
        if (pointer_map[s].father.empty()) {
            string ans;
            bool is_first = true;
            while(!v.empty()) {
                if (is_first) {
                    ans = v.back();
                    is_first = false;
                    v.pop_back();
                    continue;
                }
                ans += " -> " + v.back();
                v.pop_back();
            }
            return ans;
        }
        return get_related_var(pointer_map[s].father);
    }

    void TableBuilder::add_pointer_son(string &father, string &son) {
        pointer_map[father].son.push_back(son);
        pointer_map[son].father = father;
    }

    void TableBuilder::extract_info(const CallInst *ins_ptr) {
        auto fn = ins_ptr->getCalledFunction();
        if (fn) {
            if (fn->getName() == "malloc") {
                for (auto arg = ins_ptr->arg_begin(); arg != ins_ptr->arg_end(); ++ arg) {
                    if (auto val = dyn_cast<ConstantInt>(arg)) {
                        auto name = ins_ptr->getName();
                        malloc_info[name] = val->getZExtValue();
#if DEBUG
                        errs() << "name: " << name << " " << val->getZExtValue() << "\n";
#endif
                    }
                }
            }
        } else {
            if (ins_ptr->getNumOperands() > 1) {
                if (auto ce = dyn_cast<ConstantExpr>(ins_ptr->getOperand(1))) {
                    if (ce->getNumOperands() && ce->getOperand(0)->getName() == "free") {
                        string var = ins_ptr->getOperand(0)->getName();
                        table.free(var);
#if DEBUG
                        errs() << var << " is free!\n";
#endif
                    }
                }
            }
        }
    }

    void TableBuilder::extract_info(const BitCastInst *ins_ptr) {
        auto left_name = ins_ptr->getName();
        auto right_name = ins_ptr->getOperand(0)->getName();
#if DEBUG
        errs() << "\nnum operand: " << ins_ptr->getNumOperands() << "\n";
        errs() << "left name: " << left_name << "\n";
        errs() << "right name: " << right_name << "\n";
#endif
        auto right_type = dyn_cast<PointerType>(ins_ptr->getOperand(0)->getType());
        auto left_type = dyn_cast<PointerType>(ins_ptr->getValueName()->getValue()->getType());
        if (right_type && left_type) {
            auto left_width = left_type->getElementType()->getIntegerBitWidth();
            auto right_width = right_type->getElementType()->getIntegerBitWidth();
            auto block_num = left_width / right_width;
#if DEBUG
            errs() << left_width << " " << right_width << " " << block_num << "\n";
#endif
            string pointer_name = left_name;
            table.malloc(pointer_name, block_num);
            return;
        };
        errs() << "extract bitcast inst error!\n";
        exit(1);
    }

    void TableBuilder::extract_info(const GetElementPtrInst *ins_ptr) {
        string left_name = ins_ptr->getName();
        if (ins_ptr->getNumOperands() == 2) {
            string right_name = ins_ptr->getOperand(0)->getName();
            auto delta = ins_ptr->getOperand(1);
            auto delta_val = InstructionParser::parse_llvm_value_to_string(delta);
            int addr = table.get_address(right_name, 1);
            addr += atoi(delta_val.c_str());
            if (!table.check_out_bound(right_name, atoi(delta_val.c_str()))){
                cout << get_related_var(right_name) << "\n";
            }
#if DEBUG
            errs() << "\nnum operand: " << ins_ptr->getNumOperands() << "\n";
            errs() << "left: " << left_name << "\n";
            errs() << "right: " << right_name << "\n";
            errs() <<  "delta: " << delta_val << "\n";
#endif
            Payload payload(left_name, to_string(addr));
            table.add_data(payload);
        } else if (ins_ptr->getNumOperands() == 3) {
            string right_name = ins_ptr->getOperand(0)->getName();
            auto delta = ins_ptr->getOperand(1);
            auto delta_val = InstructionParser::parse_llvm_value_to_string(delta);
            auto delta2 = ins_ptr->getOperand(2);
            auto delta_val2 = InstructionParser::parse_llvm_value_to_string(delta2);
            int addr = table.get_address(right_name, 1);
            int offset = atoi(delta_val.c_str()) + atoi(delta_val2.c_str());
            addr += offset;
            if (!table.check_out_bound(right_name, offset)) {
                cout << get_related_var(right_name) << "\n";
            }
#if DEBUG
            errs() << "\nnum operand: " << ins_ptr->getNumOperands() << "\n";
            errs() << "left: " << left_name << "\n";
            errs() << "right: " << right_name << "\n";
            errs() <<  "delta: " << delta_val << "\n";
            errs() <<  "delta2: " << delta_val2 << "\n";
#endif
            Payload payload(left_name, to_string(addr));
            table.add_data(payload);
        }
    }

    void TableBuilder::set_error_manager(shared_ptr<ErrorManager> &em_ptr) {
        error_ptr = em_ptr;
        table.set_error_manager(em_ptr);
    }

};