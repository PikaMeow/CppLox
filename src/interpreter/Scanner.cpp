//
// Created by pikay on 2022/9/29.
//

#include "Scanner.h"

namespace Interpreter {
    std::vector<Token> Scanner::Scan() {
        while(!isAtEnd()) {
            start = current;
            scanToken();
        }

//        for(auto token: tokenList) {
//            std::cout << token.toString() << std::endl;
//        }
        return tokenList;
    }

    void Scanner::addToken(TokenType type) {
        addToken(type, NULL);
    }

    void Scanner::addToken(TokenType type, std::any object) {
        auto lexeme = text.substr(start, current - start);
        tokenList.push_back({ type, lexeme, line, object });
    }

    bool Scanner::isAtEnd() {
        return current >= text.length();
    }

    char Scanner::advance() {
        return text[current++];
    }

    bool Scanner::match(char expected) {
        if (isAtEnd() || peek() != expected) return false;
        current++;
        return true;
    }

    char Scanner::peek() {
        if (isAtEnd()) return '\0';
        return text[current];
    }

    char Scanner::peekNext() {
        if (current + 1 > text.length()) return '\0';
        return text[current + 1];
    }

    void Scanner::comments() {
        while (!isAtEnd() || peek() != '\n') {
            advance();
        }
    }

    void Scanner::string() {
        while(peek() != '"' && !isAtEnd()) {
            if (peek() == '\n') line++;
            advance();
        }

        if (isAtEnd()) {
            CppLoxErrorHandler::error(line, "Non-terminated string");
        } else {
            advance();
            addToken(STRING, text.substr(start + 1, current - start - 2));
        }
    }

    void Scanner::number() {
        while (std::isdigit(peek()) || (peek() == '.' && std::isdigit(peekNext()))) {
            advance();
        }
        addToken(NUMBER,  std::stod(text.substr(start, current - start)));
    }

    void Scanner::literal() {
        while (isalnum(peek()) || peek() == '_') {
            advance();
        }
        auto lexeme = text.substr(start, current - start);
        auto keyword = keywords.find(lexeme);
        if (keyword != keywords.end()) {
            addToken(keyword->second);
        } else {
            addToken(IDENTIFIER);
        }
    }

    void Scanner::scanToken() {
        char ch = advance();
        switch (ch) {
            case ',': addToken(COMMA); break;
            case ';': addToken(SEMICOLON); break;
            case '.': addToken(POINT); break;
            case '+': addToken(ADD); break;
            case '-': addToken(SUB); break;
            case '*': addToken(MULTI); break;
            case '{': addToken(LEFT_BRACE); break;
            case '}': addToken(RIGHT_BRACE); break;
            case '(': addToken(LEFT_PAREN); break;
            case ')': addToken(RIGHT_PAREN); break;
            case '"': string(); break;
            case '\n': line++; break;
            case ' ':
            case '\r':
            case '\t':
                break;
            case '/':
                if (match('/')) {
                    comments();
                } else {
                    addToken(DIVIDE);
                }
                break;
            case '=':
                match('=') ? addToken(EE) : addToken(EQUAL);
                break;
            case '>':
                match('=') ? addToken(GE) : addToken(GREATER);
                break;
            case '<':
                match('=') ? addToken(LE) : addToken(LESS);
                break;
            case '!':
                match('=') ? addToken(NE) : addToken(NOT);
                break;
            default:
                if (std::isdigit(ch)) {
                    number();
                } else if (std::isalpha(ch) || ch == '_'){
                    literal();
                } else {
                    CppLoxErrorHandler::error(line, "Unexpected character");
                }
                break;
        }
    }
} // Interpreter