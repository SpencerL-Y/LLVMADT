#ifndef SVCompParser_hpp
#define SVCompParser_hpp

#include <stdlib.h>
#include <vector>
#include <list>
#include <set>
#include <iostream>
#include <yaml-cpp/yaml.h>

namespace llvmadt
{
    
class SVCompParser
{
private:
    /* data */
public:
    SVCompParser(/* args */);
    ~SVCompParser();
    std::string parseSVCompYamlInputFile(std::string path);
};

} // namespace llvmadt


#endif