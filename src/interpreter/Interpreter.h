//
// Created by pikay on 2022/10/7.
//

#ifndef CPPLOX_INTERPRETER_H
#define CPPLOX_INTERPRETER_H

#include "../ast/Stmt.h"
#include "Environment.h"

namespace Interpreter {

class Interpreter: public Expr::VisitorR<std::any>, public Stmt::Visitor {
    private:
        std::vector<std::shared_ptr<Stmt>> stmts;
        std::shared_ptr<Environment> environment;
        void execute(std::shared_ptr<Stmt> stmt);
        bool isTruthy(const std::any& expr);
        std::any evaluate(std::shared_ptr<Expr> expr);
        void executeBlock(const std::vector<std::shared_ptr<Stmt>>& stmts, const std::shared_ptr<Environment> environment);

    public:
        explicit Interpreter(const std::vector<std::shared_ptr<Stmt>>& stmts): stmts(stmts) {
            environment = std::make_shared<Environment>();
        }
        void Interpret();

        void visitBinaryExpr(Expr::Binary* expr) override;
        void visitGroupingExpr(Expr::Grouping* expr) override;
        void visitLiteralExpr(Expr::Literal* expr) override;
        void visitUnaryExpr(Expr::Unary* expr) override;
        void visitVariableExpr(Expr::Variable* expr) override;
        void visitAssignExpr(Expr::Assign* expr) override;

        void visitExpressionStmt(Stmt::Expression* stmt) override;
        void visitPrintStmt(Stmt::Print* stmt) override;
        void visitVarStmt(Stmt::Var* stmt) override;
        void visitBlockStmt(Stmt::Block* stmt) override {
            executeBlock(stmt->stmts, std::make_shared<Environment>(environment));
        }
    };
}



#endif //CPPLOX_INTERPRETER_H
