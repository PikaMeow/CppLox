//
// Created by pikay on 2022/10/7.
//

#include "Interpreter.h"

namespace Interpreter {

    std::any Interpreter::evaluate(std::shared_ptr<Expr> expr) {
        return expr->accept(*this);
    }

    bool Interpreter::isTruthy(const std::any &expr) {
        if (!expr.has_value()) {
            return false;
        }
        bool value;
        if (Common::checkValueType<bool>(expr, value)) {
            return value;
        }
        return true;
    }

    void Interpreter::Interpret() {
        try {
            for(auto& stmt: stmts) {
                execute(stmt);
            }
        } catch (RuntimeError& err) {
            CppLoxErrorHandler::runtimeError(err);
        }
    }

    void Interpreter::visitBinaryExpr(Expr::Binary *expr) {
        auto left = evaluate(expr->left);
        auto right = evaluate(expr->right);

        double lOperand, rOperand;
        bool isNumberOperand = (Common::checkValueType<double>(left, lOperand) && Common::checkValueType<double>(right, rOperand));
        if (expr->op.type != ADD and !isNumberOperand) {
            throw RuntimeError(expr->op, "Operands must both be number");
        }

        switch (expr->op.type) {
            case MULTI: this -> result = lOperand * rOperand; break;
            case DIVIDE: this -> result = lOperand / rOperand; break;
            case SUB: this -> result = lOperand - rOperand; break;
            case GREATER: this -> result = lOperand > rOperand; break;
            case LESS: this -> result = lOperand < rOperand; break;
            case GE: this ->result = lOperand >= rOperand; break;
            case LE: this -> result = lOperand <= rOperand; break;
            case EE: this -> result = lOperand == rOperand; break;
            case NE: this -> result = lOperand != rOperand; break;
            case ADD:
                if (isNumberOperand) {
                    this -> result = lOperand + rOperand;
                } else {
                    std::string lStr, rStr;
                    if (Common::checkValueType<std::string>(left, lStr) && Common::checkValueType<std::string>(right, rStr)) {
                        this -> result = lStr + rStr;
                    } else {
                        throw RuntimeError(expr->op, "Operands must both be number or both be string");
                    }
                }
                break;
        }
    }

    void Interpreter::visitGroupingExpr(Expr::Grouping *expr) {
        this->result = evaluate(expr->expression);
    }

    void Interpreter::visitUnaryExpr(Expr::Unary *expr) {
        auto result = evaluate(expr->right);
        switch (expr->op.type) {
            case NOT:
                this -> result = !isTruthy(result);
                break;
            case SUB:
                double operand;
                if (Common::checkValueType<double>(result, operand)) {
                    this -> result = -operand;
                } else {
                    throw RuntimeError(expr->op, "Operand must be number");
                }
                break;
        }
    }

    void Interpreter::visitLiteralExpr(Expr::Literal *expr) {
        this->result = expr->value.value;
    }
}