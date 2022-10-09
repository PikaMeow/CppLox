#include <iostream>

#include "./interpreter/CppLox.h"
#include "./common/AstGenerator.h"

int main(int argc, char** argv) {
    // AstGenerator::generate("D:\\Seafile\\Codes\\CppLox\\src\\ast");
    std::vector<std::string> params;
    for(int i = 1; i < argc; i++) {
        params.push_back(argv[i]);
    }
    Interpreter::CppLox interpreter;
    interpreter.run(params);
}
