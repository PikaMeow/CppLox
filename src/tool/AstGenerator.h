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
#include "../common/Utils.h"

struct Template {
public:
    std::string macro;
    std::string include;
    bool visitReturned;

    Template(const std::string& baseName, const std::string& include, bool visitReturned = false): include(include), visitReturned(visitReturned) {
        macro = "#ifndef CPPLOX_" + baseName + "_H\n#define CPPLOX_" + baseName + "_H\n\n";
    }

};

class AstGenerator {
public:
    static void generate(const std::string& outputDir);
    static void defineAst(const std::string& outputDir, const std::string& baseName, const std::map<std::string, std::string>& types, const Template& extra);
    static void defineType(std::ofstream& out, const std::string& baseName, const std::string& className, const std::string& fieldList);
};


#endif //CPPLOX_ASTGENERATOR_H
