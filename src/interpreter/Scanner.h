//
// Created by pikay on 2022/9/29.
//

#ifndef CPPLOX_SCANNER_H
#define CPPLOX_SCANNER_H

#include <iomanip>
#include <string>
#include <any>
#include <vector>
#include <iostream>
#include <set>
#include <map>
#include "../common/Utils.h"
#include "CppLoxErrorHandler.h"
#include "Token.h"

namespace Interpreter {

    class Scanner {
    private:
        int start = 0;
        int current = 0;
        int line = 1;
        std::vector<Token> tokenList;
        std::string text;
        std::map<std::string, TokenType> keywords {
                {"true", TRUE}, {"false", FALSE}, {"nil", NIL}, {"and", AND}, {"or", OR},
                {"if", IF}, {"else", ELSE}, {"while", WHILE}, {"for", FOR}, {"return", RETURN},
                {"fun", FUN}, {"class", CLASS}, {"var", VAR}, {"this", THIS}, {"super", SUPER},
                {"print", PRINT},
        };

        void addToken(TokenType type);
        void addToken(TokenType type, std::any object);
        bool isAtEnd();
        char advance();
        bool match(char expected);
        char peek();
        char peekNext();
        void comments();
        void string();
        void number();
        void literal();
        void scanToken();

    public:
        Scanner(std::string& text): text(text) {}
        std::vector<Token> Scan();
    };

} // Interpreter

#endif //CPPLOX_SCANNER_H
