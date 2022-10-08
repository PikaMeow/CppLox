//
// Created by pikay on 2022/10/5.
//

#include "AstGenerator.h"

void AstGenerator::generate(const std::string &outputDir) {
    defineAst(outputDir, "Expr", {
            {"Binary" , "std::shared_ptr<Expr> left, Token op, std::shared_ptr<Expr> right"},
            {"Grouping", "std::shared_ptr<Expr> expression"},
            {"Literal", "Token value"},
            {"Unary", "Token op, std::shared_ptr<Expr> right"},
    });
}

void AstGenerator::defineAst(const std::string &outputDir, const std::string &baseName,
                             const std::map<std::string, std::string> &types) {
    std::filesystem::path fullPath(outputDir);
    fullPath /= (baseName + ".h");
    auto str = fullPath.string();
    std::ofstream out(fullPath.string());
    out << R"(
#ifndef CPPLOX_EXPR_H
#define CPPLOX_EXPR_H

#include "../interpreter/Scanner.h"

namespace Interpreter {
)";
    out << "    class " << baseName << " {";
    out << R"(
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
)";
    for (auto& type: types) {
        out << "        class " << type.first << ";\n";
    }

    out << R"(
    };

    class Expr::VisitorBase {
    public:
)";
    for(auto& type: types) {
        out << "        virtual void visit" << type.first << baseName << "(" << type.first << "* expr) = 0;\n";
    }

    out << R"(
    };

    template <typename R>
    class Expr::Visitor: public Expr::VisitorBase {
    public:
        R result;
    };

)";
    for (auto& type: types) {
        defineType(out, baseName, type.first, type.second);
    }

    out << R"(
}

#endif //CPPLOX_EXPR_H
)";
    out << std::endl;
    out.close();
}

void AstGenerator::defineType(std::ofstream &out, const std::string &baseName, const std::string &className,
                              const std::string &fieldList) {
    out << "    class " << baseName << "::" << className << ": public " << baseName << "{\n    public:\n";

    auto fields = Common::split(fieldList, ',');

    for(auto& field:fields) {
        out << "        " << field << ";\n";
    }
    out << "\n        " << className << "(" << fieldList << "):";

    for(size_t i = 0; i < fields.size(); i++) {
        auto name = Common::split(fields[i], ' ')[1];
        out << name << "(" << name << ")";
        if (i != fields.size() - 1) out << ",";
        out << " ";
    }

    out << "{}\n";
    out << "        void doAccept(VisitorBase& visitor) override {\n";
    out << "            visitor.visit" << className << baseName << "(this);";
    out << R"(
        };
    };

)";
}
