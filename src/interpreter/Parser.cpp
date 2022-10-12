//
// Created by pikay on 2022/10/5.
//

#include "Parser.h"

namespace Interpreter {
    bool Parser::isAtEnd() {
        return current >= tokenList.size();
    }

    Token &Parser::advance() {
        return tokenList[current++];
    }

    Token &Parser::peek() {
        return tokenList[current];
    }

    Token &Parser::previous() {
        return tokenList[current - 1];
    }

    bool Parser::match(const std::vector<TokenType> &types) {
        for (auto &type: types)
            if (check(type)) {
                advance();
                return true;
            }

        return false;
    }

    bool Parser::check(TokenType expected) {
        if (isAtEnd()) return false;
        return peek().type == expected;
    }

    Token &Parser::consume(TokenType type, const std::string &message) {
        if (check(type)) return advance();
        throw error(previous(), message);
    }

    ParseError Parser::error(Token &token, const std::string &message) {
        CppLoxErrorHandler::error(token, message);
        throw ParseError(message);
    }

/*
 * expression → equality ;
 */
    std::shared_ptr<Expr> Parser::expression() {
        return assign();
    }

/*
 * equality → comparison ( ( "!=" | "==" ) comparison )* ;
 */
    std::shared_ptr<Expr> Parser::equality() {
        auto expr = comparison();
        while (match({ EE, NE })) {
            Token& op = previous();
            auto right = comparison();
            expr = std::make_shared<Expr::Binary>(expr, op, right);
        }

        return expr;
    }

/*
 * comparison → term ( ( ">" | ">=" | "<" | "<=" ) term )* ;
 */
    std::shared_ptr<Expr> Parser::comparison() {
        auto expr = term();
        while (match({ GE, LE, GREATER, LESS })) {
            Token& op = previous();
            auto right = term();
            expr = std::make_shared<Expr::Binary>(expr, op, right);
        }

        return expr;
    }

/*
 * term → factor ( ( "-" | "+" ) factor )* ;
 */
    std::shared_ptr<Expr> Parser::term() {
        auto expr = factor();
        while (match({ ADD, SUB })) {
            Token& op = previous();
            auto right = factor();
            expr = std::make_shared<Expr::Binary>(expr, op, right);
        }

        return expr;
    }

/*
 * factor → unary ( ( "/" | "*" ) unary )* ;
 */
    std::shared_ptr<Expr> Parser::factor() {
        auto expr = unary();
        while (match({ MULTI, DIVIDE })) {
            Token& op = previous();
            auto right = unary();
            expr = std::make_shared<Expr::Binary>(expr, op, right);
        }

        return expr;
    }

/*
 * unary → ( "!" | "-" ) unary | primary ;
 */
    std::shared_ptr<Expr> Parser::unary() {
        if (match({ NOT, SUB })) {
            Token& op = previous();
            auto right = unary();
            return std::make_shared<Expr::Unary>(op, right);
        }
        return primary();
    }

/*
 * primary → NUMBER | STRING | "true" | "false" | "nil" | "(" expression ")" ;
 */
    std::shared_ptr<Expr> Parser::primary() {
        if (match({ TRUE, FALSE, NIL, NUMBER, STRING }))
            return std::make_shared<Expr::Literal>(previous());
        if (match({ IDENTIFIER }))
            return std::make_shared<Expr::Variable>(previous());
        if (match({ LEFT_PAREN })) {
            auto expr = expression();
            consume(RIGHT_PAREN, "Expect ')' after expression.");
            return std::make_shared<Expr::Grouping>(expr);
        }

        throw error(peek(), "Unexpected token '" + peek().lexeme + "' ");
    }

    std::vector<std::shared_ptr<Stmt>> Parser::Parse() {
        std::vector<std::shared_ptr<Stmt>> statements;
        try {
            while (!isAtEnd()) {
                statements.emplace_back(declaration());
            }
        } catch (ParseError& e) {
        }

        return statements;
    }

    std::shared_ptr<Expr> Parser::assign() {
        auto expr = equality();
        if (match({ EQUAL })) {
            Token equals = previous();
            auto value = assign();

            if (auto target = dynamic_cast<Expr::Variable*>(expr.get())) {
                Token name = target->name;
                return std::make_shared<Expr::Assign>(name, value);
            }

            error(equals, "Invalid assignment types.");
        }
        return expr;
    }

    std::shared_ptr<Stmt> Parser::expressionStmt() {
        auto expr = expression();
        consume(SEMICOLON, "Statement must ends with semicolon.");
        return std::make_shared<Stmt::Expression>(expr);
    }

    std::shared_ptr<Stmt> Parser::printStmt() {
        auto expr = expression();
        consume(SEMICOLON, "Statement must ends with semicolon.");
        return std::make_shared<Stmt::Print>(expr);
    }

    std::shared_ptr<Stmt> Parser::statement() {
        if (match({ PRINT })) {
            return printStmt();
        }
        if (match({ LEFT_BRACE })) {
            return blockStmt();
        }
        return expressionStmt();
    }

    std::shared_ptr<Stmt> Parser::varDecl() {
        auto name = consume(IDENTIFIER, "Expect variable name.");
        auto initializer = std::make_shared<Expr>();
        if (match({ EQUAL })) {
            initializer = expression();
        }
        consume(SEMICOLON, "Expect ';' after variable declaration.");
        return std::make_shared<Stmt::Var>(name, initializer);
    }

    std::shared_ptr<Stmt> Parser::declaration() {
        if (match({ VAR })) {
            return varDecl();
        }
        return statement();
    }

    std::shared_ptr<Stmt> Parser::blockStmt() {
        std::vector<std::shared_ptr<Stmt>> stmts;
        while(!isAtEnd() && !check({ RIGHT_BRACE })) {
            auto stmt = declaration();
            stmts.emplace_back(stmt);
        }
        consume(RIGHT_BRACE, "Expect '}' after block.");
        return std::make_shared<Stmt::Block>(stmts);
    }
}

