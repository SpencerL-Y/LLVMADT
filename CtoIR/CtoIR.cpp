#include <iostream>
#include <cstdlib>
#include <stdio.h>
#include <cstring>

using namespace std;

int main(int argc, char** argv)
{
    string c_path = argv[1];
    string file = c_path.substr(0, c_path.rfind(".")); 
    string filename = file.substr(file.rfind("/") + 1, -1);
    // cout << filename << endl;
    string command1 = "clang -O0 " 
        + file + ".c "
        + "-fno-discard-value-names -emit-llvm -S -o "
        + filename + ".ll";
    // cout << command1 << endl;
    const char *sysCommand1 = command1.data();
    system(sysCommand1);
    string command2 = "opt -mem2reg -instnamer "
        + filename +".ll "
        + "-o "
        + filename 
        +".bc";
    const char *sysCommand2 = command2.data();
    system(sysCommand2);
    string command3 = "llvm-dis " 
        + filename + ".bc -o "
        + "../testIRfile/"
        + filename + ".ll";
    const char *sysCommand3 = command3.data();
    system(sysCommand3);
    string delCom = "rm -rf " + filename + ".bc && rm -rf " + filename + ".ll" ;
    const char* sysdelCom = delCom.data(); 
    cout << sysdelCom << endl;
    system(sysdelCom);
    return 0;
}