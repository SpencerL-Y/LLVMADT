
#include <stdlib.h>
#include <cstdlib>
#include <string>
#include <iostream>

namespace llvmadt
{
    std::string generateLLVMFile(std::string sourcePath){
        std::string c_path = sourcePath;
        std::string file = c_path.substr(0, c_path.rfind(".")); 
        std::string filename = file.substr(file.rfind("/") + 1, -1);
        // cout << filename << endl;
        std::string command1 = "clang -O0 " 
            + file + ".c "
            + "-fno-discard-value-names -emit-llvm -S -o "
            + filename + ".ll";
        // cout << command1 << endl;
        const char *sysCommand1 = command1.data();
        std::system(sysCommand1);
        std::string command2 = "opt -mem2reg -instnamer "
            + filename +".ll "
            + "-o "
            + filename 
            +".bc";
        const char *sysCommand2 = command2.data();
        std::system(sysCommand2);
        std::string command3 = "llvm-dis " 
            + filename + ".bc -o "
            + "../../testIRfile/loop-simple/"
            + filename + ".ll";
        const char *sysCommand3 = command3.data();
        std::system(sysCommand3);
        std::string delCom = "rm -rf " + filename + ".bc && rm -rf " + filename + ".ll" ;
        const char* sysdelCom = delCom.data(); 
        std::cout << sysdelCom << std::endl;
        std::system(sysdelCom);
        return "../../testIRfile/loop-simple/" + filename + ".ll";
    }   
} // namespace llvmadt
