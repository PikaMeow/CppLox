//
// Created by pikay on 2022/10/5.
//

#ifndef CPPLOX_ASTGENERATOR_H
#define CPPLOX_ASTGENERATOR_H


#include <string>
#include <vector>
#include <filesystem>
#include <fstream>
#include <map>
#include "Utils.h"

class AstGenerator {
public:
    static void generate(const std::string& outputDir);
    static void defineAst(const std::string& outputDir, const std::string& baseName, const std::map<std::string, std::string>& types);
    static void defineType(std::ofstream& out, const std::string& baseName, const std::string& className, const std::string& fieldList);
};


#endif //CPPLOX_ASTGENERATOR_H
