#ifndef SVCompParser_hpp
#define SVCompParser_hpp

#include <stdlib.h>
#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>  
#include <yaml-cpp/yaml.h>

namespace llvmadt
{
    
class SVCompParser
{
private:
    std::string format_version;
    std::string input_files;
    std::string properties;
public:
    SVCompParser(/* args */);
    ~SVCompParser();
    std::string parseSVCompYamlFile(std::string path);
    std::string extractReachErrorResult();
    std::string getInputFiles();
    std::string getProperties();
    std::string getFormatVersion();
};

} // namespace llvmadt


#endif