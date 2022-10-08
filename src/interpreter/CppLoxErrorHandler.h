//
// Created by pikay on 2022/10/4.
//

#ifndef CPPLOX_CPPLOXERRORHANDLER_H
#define CPPLOX_CPPLOXERRORHANDLER_H

#include <string>
#include <iostream>
#include "Token.h"

namespace Interpreter {

    static bool hasError = false;
    static bool hasRuntimeError = false;

    class ParseError: public std::runtime_error {
    public:
        explicit ParseError(const std::string& what = ""): std::runtime_error(what) {}
    };

    class RuntimeError: public std::runtime_error {
    public:
        Token token;
        explicit RuntimeError(const Token& token, const std::string& what = ""): std::runtime_error(what), token(token) {}
    };

    class CppLoxErrorHandler {
    private:
        static void report(int line, const std::string& where, const std::string& message) {
            std::cerr << "[line " << line << "] Error" << where << ": " << message << std::endl;
            hasError = true;
        }
    public:
        static void error(int line, const std::string& message) {
            report(line, "", message);
        }

        static void error(const Token& token, const std::string& message) {
            report(token.line, " at '" + token.lexeme + "'", message);
        }

        static void runtimeError(const RuntimeError& err) {
            std::cerr << err.what() << "\n[line " << err.token.line << " ]";
            hasRuntimeError = true;
        }
    };

} // Interpreter

#endif //CPPLOX_CPPLOXERRORHANDLER_H
