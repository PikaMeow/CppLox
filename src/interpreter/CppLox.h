//
// Created by pikay on 2022/9/29.
//

#ifndef CPPLOX_CPPLOX_H
#define CPPLOX_CPPLOX_H

#include <iostream>
#include <fstream>
#include <sstream>
#include "Scanner.h"
#include "CppLoxErrorHandler.h"
#include "AstPrinter.h"

namespace Interpreter {

    class CppLox {
    private:
        void runCore(std::string code);

    public:
        void run(std::vector<std::string>& params);
        void runPrompt();
        void runFile(std::string& filePath);
        void testAst();
    };

} // Interpreter

#endif //CPPLOX_CPPLOX_H
