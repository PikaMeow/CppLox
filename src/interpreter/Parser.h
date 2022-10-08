//
// Created by pikay on 2022/10/5.
//

#ifndef CPPLOX_PARSER_H
#define CPPLOX_PARSER_H


#include <vector>
#include "./Scanner.h"
#include "../ast/Expr.h"

namespace Interpreter {

    class Parser {
    private:
        int current = 0;
        std::vector<Token> tokenList;
        const ParseError parseError = ParseError();

        bool isAtEnd();
        Token& advance();
        Token& peek();
        Token& previous();
        bool match(const std::vector<TokenType>& types);
        bool check(TokenType expected);

        Token& consume(TokenType type, const std::string& message);
        ParseError error(Token& token, const std::string& message);

        std::shared_ptr<Expr> expression();
        std::shared_ptr<Expr> equality();
        std::shared_ptr<Expr> comparison();
        std::shared_ptr<Expr> term();
        std::shared_ptr<Expr> factor();
        std::shared_ptr<Expr> unary();
        std::shared_ptr<Expr> primary();

    public:
        Parser(std::vector<Token>& tokenList): tokenList(tokenList) {}
        std::shared_ptr<Expr> Parse();
    };
}



#endif //CPPLOX_PARSER_H