#ifndef CPPLOX_Stmt_H
#define CPPLOX_Stmt_H

#include "../interpreter/Scanner.h"
#include "./Expr.h"

namespace Interpreter {
    class Stmt {
    public:
        class Visitor;
        void accept(Visitor& visitor) {
            doAccept(visitor);
        };
        virtual void doAccept(Visitor& visitor) {}
        class Block;
        class Expression;
        class Print;
        class Var;
    };

    class Stmt::Visitor {
    public:
        virtual void visitBlockStmt(Block* expr) = 0;
        virtual void visitExpressionStmt(Expression* expr) = 0;
        virtual void visitPrintStmt(Print* expr) = 0;
        virtual void visitVarStmt(Var* expr) = 0;
    };

    class Stmt::Block: public Stmt{
    public:
        std::vector<std::shared_ptr<Stmt>> stmts;

        Block(std::vector<std::shared_ptr<Stmt>> stmts):stmts(stmts) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitBlockStmt(this);
        };
    };

    class Stmt::Expression: public Stmt{
    public:
        std::shared_ptr<Expr> expr;

        Expression(std::shared_ptr<Expr> expr):expr(expr) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitExpressionStmt(this);
        };
    };

    class Stmt::Print: public Stmt{
    public:
        std::shared_ptr<Expr> expr;

        Print(std::shared_ptr<Expr> expr):expr(expr) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitPrintStmt(this);
        };
    };

    class Stmt::Var: public Stmt{
    public:
        Token name;
        std::shared_ptr<Expr> initializer;

        Var(Token name, std::shared_ptr<Expr> initializer):name(name), initializer(initializer) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitVarStmt(this);
        };
    };

}

#endif