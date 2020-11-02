#include "../../../include/checker/parser/SVCompParser.hpp"

namespace llvmadt
{
    
SVCompParser::SVCompParser(/* args */)
{
    
}

SVCompParser::~SVCompParser()
{
    
}

std::string SVCompParser::parseSVCompYamlFile(std::string path){
    this->input_files = "";
    this->format_version = "";
    this->properties = "";
    std::ifstream in(path.c_str(), std::ios::in);
    std::stringstream ss;
    ss << in.rdbuf();
    std::string yamlStr = "";
    if(!in){
        std::cout << "error: yaml path invalid" << std::endl; 
    } else {
        yamlStr =  ss.str();
    }
    std::cout << "yamlStr: " << yamlStr << std::endl;
    YAML::Node node = YAML::Load(yamlStr);
    this->input_files = node["input_files"].as<std::string>();
    this->format_version = node["format_version"].as<std::string>();
    //his->properties = node["properties"].as<std::string>();

    std::cout << "input files: " << this->input_files << std::endl;
    std::cout << "format version: " << this->format_version << std::endl;
    //std::cout << "properties: " << this->properties << std::endl;

    const YAML::Node& property = node["properties"];
    int i = 0;
    for(auto it = property.begin(); it != property.end(); ++it){
        YAML::Node property_file = property[i]["property_file"];
        YAML::Node verdict = property[i]["expected_verdict"];
        std::string pathOfProperty = property_file.as<std::string>();
        
        std::cout << "prp: " << pathOfProperty << std::endl;
        if(verdict){
            std::string expectedVerdict = verdict.as<std::string>();
            std::cout << "verdict: " << expectedVerdict << std::endl;
        }
        i++;
    }

    return yamlStr;
}

} // namespace llvmadt

