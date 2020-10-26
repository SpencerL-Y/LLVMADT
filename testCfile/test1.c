// #include <iostream>
// using namespace std;

// clang++ -O0 test2.cpp -fno-discard-value-names -DLLVM_ENABLE_ASSERTIONS=On -emit-llvm -S -o test4.ll

int x, y;

int main()
{
    while(1)
    {
        x = 1;
        x = 6;
        y = 1;
        
        while(x > 0)
        {
            x--;
            if ( x <= 1)
                y = 0;
        }
    }    
    return 0;
}

