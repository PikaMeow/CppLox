//
// Created by pikay on 2022/10/5.
//

#ifndef CPPLOX_ASTPRINTER_H
#define CPPLOX_ASTPRINTER_H

#include "../ast/Expr.h"

namespace Interpreter {
    class AstPrinter: public Expr::Visitor<std::string> {
    private:
        std::string parenthesize(const std::string& name, const std::vector<std::shared_ptr<Expr>>& exprs) {
            std::stringstream buffer;
            buffer << "(" << name;
            for(auto expr: exprs) {
                buffer << " " << expr->accept(*this);
            }
            buffer << ")";
            return buffer.str();
        }
    public:
        std::string print(Expr& expr) {
            return expr.accept(*this);
        }

        void visitBinaryExpr(Expr::Binary* expr) override {
            this -> result = parenthesize(expr->op.lexeme, { expr->left, expr->right} );
        }
        void visitGroupingExpr(Expr::Grouping* expr) override {
            this -> result = parenthesize("group", { expr->expression } );
        }
        void visitLiteralExpr(Expr::Literal* expr) override {
            this -> result = expr->value.lexeme;
        }
        void visitUnaryExpr(Expr::Unary* expr) override {
            this -> result = parenthesize(expr->op.lexeme,  { expr->right } );
        }
    };
}




#endif //CPPLOX_ASTPRINTER_H
