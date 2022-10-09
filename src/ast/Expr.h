
#ifndef CPPLOX_EXPR_H
#define CPPLOX_EXPR_H

#include "../interpreter/Scanner.h"

namespace Interpreter {
    class Expr {
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
        class Binary;
        class Grouping;
        class Literal;
        class Unary;
    };

    class Expr::VisitorBase {
    public:
        virtual void visitBinaryExpr(Binary* expr) = 0;
        virtual void visitGroupingExpr(Grouping* expr) = 0;
        virtual void visitLiteralExpr(Literal* expr) = 0;
        virtual void visitUnaryExpr(Unary* expr) = 0;
    };

    template <typename R>
    class Expr::Visitor: public Expr::VisitorBase {
    public:
        R result;
    };

    class Expr::Binary: public Expr{
    public:
        std::shared_ptr<Expr> left;
        Token op;
        std::shared_ptr<Expr> right;

        Binary(std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right):left(left), op(op), right(right) {}
        void doAccept(VisitorBase& visitor) override {
            visitor.visitBinaryExpr(this);
        };
    };

    class Expr::Grouping: public Expr{
    public:
        std::shared_ptr<Expr> expression;

        Grouping(std::shared_ptr<Expr> expression):expression(expression) {}
        void doAccept(VisitorBase& visitor) override {
            visitor.visitGroupingExpr(this);
        };
    };

    class Expr::Literal: public Expr{
    public:
        Token value;

        Literal(Token value):value(value) {}
        void doAccept(VisitorBase& visitor) override {
            visitor.visitLiteralExpr(this);
        };
    };

    class Expr::Unary: public Expr{
    public:
        Token op;
        std::shared_ptr<Expr> right;

        Unary(Token op, std::shared_ptr<Expr> right):op(op), right(right) {}
        void doAccept(VisitorBase& visitor) override {
            visitor.visitUnaryExpr(this);
        };
    };


}

#endif //CPPLOX_EXPR_H

