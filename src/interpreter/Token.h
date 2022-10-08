//
// Created by pikay on 2022/10/5.
//

#ifndef CPPLOX_TOKEN_H
#define CPPLOX_TOKEN_H

#include <string>
#include <any>

namespace Interpreter {
    enum TokenType {
        // One character token
        COMMA, SEMICOLON, POINT, // , ; .
        LEFT_BRACE, RIGHT_BRACE, // { }
        LEFT_PAREN, RIGHT_PAREN, // ( )
        EQUAL, GREATER, LESS, NOT, // = > < !
        ADD, SUB, MULTI, DIVIDE, // + - * /

        // Two character token
        EE, GE, LE, NE, // ==, >=, <=, !=

        // Variant length token
        STRING, NUMBER, IDENTIFIER,

        // Keywords
        TRUE, FALSE, NIL, AND, OR,
        IF, ELSE, WHILE, FOR, RETURN,
        FUN, CLASS, VAR, THIS, SUPER,
        PRINT,

    };

    struct Token {
        TokenType type;
        std::string lexeme;
        int line;
        std::any value;

        std::string toString() {
            std::stringstream buffer;
            buffer << "Token: [ type: " << std::setw(2) << type << ", lexeme: " << std::setw(20) << lexeme << " at line " << std::setw(3) << line << " ]";
            return buffer.str();
        }
    };
}



#endif //CPPLOX_TOKEN_H
