//
// Created by pikay on 2022/10/7.
//

#ifndef CPPLOX_INTERPRETER_H
#define CPPLOX_INTERPRETER_H

#include "../ast/Expr.h"

namespace Interpreter {

    class Interpreter: public Expr::Visitor<std::any> {
    private:
        std::shared_ptr<Expr> expr;
        std::any evaluate(std::shared_ptr<Expr> expr);
        bool isTruthy(const std::any& expr);

    public:
        explicit Interpreter(std::shared_ptr<Expr> expr): expr(expr) {}
        void Interpret();

        void visitBinaryExpr(Expr::Binary* expr) override;
        void visitGroupingExpr(Expr::Grouping* expr) override;
        void visitLiteralExpr(Expr::Literal* expr) override;
        void visitUnaryExpr(Expr::Unary* expr) override;
    };
}



#endif //CPPLOX_INTERPRETER_H
