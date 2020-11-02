// #include <iostream>
// using namespace std;

// clang++ -O0 test2.cpp -fno-discard-value-names -DLLVM_ENABLE_ASSERTIONS=On -emit-llvm -S -o test4.ll
int x, y;
int main()
    x = 1;
    y = 2;
    x = 6;
    x--;
    y = x;
    return 0;
}

