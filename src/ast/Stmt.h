
#ifndef CPPLOX_STMT_H
#define CPPLOX_STMT_H

#include "../interpreter/Scanner.h"
#include "./Expr.h"

namespace Interpreter {
    class Stmt {
    public:
        class VisitorBase;
        template <typename R> class Visitor;
        template <typename R> R accept(Visitor<R>& visitor) {
            doAccept(visitor);
            R result = visitor.result;
            visitor.result = R();
            return result;
        };
        virtual void doAccept(VisitorBase& visitor) {}
        class Expression;
        class Print;
    };

    class Stmt::VisitorBase {
    public:
        virtual void visitExpressionStmt(Expression* expr) = 0;
        virtual void visitPrintStmt(Print* expr) = 0;
    };

    template <typename R>
    class Stmt::Visitor: public Stmt::VisitorBase {
    public:
        R result;
    };

    class Stmt::Expression: public Stmt{
    public:
        std::shared_ptr<Expr> expr;

        Expression(std::shared_ptr<Expr> expr):expr(expr) {}
        void doAccept(VisitorBase& visitor) override {
            visitor.visitExpressionStmt(this);
        };
    };

    class Stmt::Print: public Stmt{
    public:
        std::shared_ptr<Expr> expr;

        Print(std::shared_ptr<Expr> expr):expr(expr) {}
        void doAccept(VisitorBase& visitor) override {
            visitor.visitPrintStmt(this);
        };
    };


}

#endif //CPPLOX_STMT_H

