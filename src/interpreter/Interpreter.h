//
// Created by pikay on 2022/10/7.
//

#ifndef CPPLOX_INTERPRETER_H
#define CPPLOX_INTERPRETER_H

#include "../ast/Stmt.h"

namespace Interpreter {

class Interpreter: public Expr::Visitor<std::any>, public Stmt::Visitor<int> {
    private:
        std::vector<std::shared_ptr<Stmt>> stmts;
        int execute(std::shared_ptr<Stmt> stmt) {
            return stmt->accept(*this);
        }
        bool isTruthy(const std::any& expr);
        std::any evaluate(std::shared_ptr<Expr> expr);



    public:
        explicit Interpreter(const std::vector<std::shared_ptr<Stmt>>& stmts): stmts(stmts) {}
        void Interpret();

        void visitBinaryExpr(Expr::Binary* expr) override;
        void visitGroupingExpr(Expr::Grouping* expr) override;
        void visitLiteralExpr(Expr::Literal* expr) override;
        void visitUnaryExpr(Expr::Unary* expr) override;

        void visitExpressionStmt(Stmt::Expression* stmt) override {
            evaluate(stmt->expr);
        }

        void visitPrintStmt(Stmt::Print* stmt) override {
            auto result = evaluate(stmt->expr);
            std::cout << Common::stringify(result) << std::endl;
        }
    };
}



#endif //CPPLOX_INTERPRETER_H
