#ifndef CPPLOX_Expr_H
#define CPPLOX_Expr_H

#include "../interpreter/Scanner.h"

namespace Interpreter {
    class Expr {
    public:
        class Visitor;
        template <typename R> class VisitorR;
        template <typename R> R accept(VisitorR<R>& visitor) {
            doAccept(visitor);
            R result = visitor.result;
            visitor.result = R();
            return result;
        };
        virtual void doAccept(Visitor& visitor) {}
        class Assign;
        class Binary;
        class Grouping;
        class Literal;
        class Unary;
        class Variable;
    };

    class Expr::Visitor {
    public:
        virtual void visitAssignExpr(Assign* expr) = 0;
        virtual void visitBinaryExpr(Binary* expr) = 0;
        virtual void visitGroupingExpr(Grouping* expr) = 0;
        virtual void visitLiteralExpr(Literal* expr) = 0;
        virtual void visitUnaryExpr(Unary* expr) = 0;
        virtual void visitVariableExpr(Variable* expr) = 0;
    };

    template <typename R>
    class Expr::VisitorR: public Expr::Visitor {
    public:
        R result;
    };

    class Expr::Assign: public Expr{
    public:
        Token name;
        std::shared_ptr<Expr> value;

        Assign(Token name, std::shared_ptr<Expr> value):name(name), value(value) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitAssignExpr(this);
        };
    };

    class Expr::Binary: public Expr{
    public:
        std::shared_ptr<Expr> left;
        Token op;
        std::shared_ptr<Expr> right;

        Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right):left(left), op(op), right(right) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitBinaryExpr(this);
        };
    };

    class Expr::Grouping: public Expr{
    public:
        std::shared_ptr<Expr> expression;

        Grouping(std::shared_ptr<Expr> expression):expression(expression) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitGroupingExpr(this);
        };
    };

    class Expr::Literal: public Expr{
    public:
        Token value;

        Literal(Token value):value(value) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitLiteralExpr(this);
        };
    };

    class Expr::Unary: public Expr{
    public:
        Token op;
        std::shared_ptr<Expr> right;

        Unary(Token op, std::shared_ptr<Expr> right):op(op), right(right) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitUnaryExpr(this);
        };
    };

    class Expr::Variable: public Expr{
    public:
        Token name;

        Variable(Token name):name(name) {}
        void doAccept(Visitor& visitor) override {
            visitor.visitVariableExpr(this);
        };
    };

}

#endif