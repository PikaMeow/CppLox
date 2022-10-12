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
            {"Variable", "Token name"},
            {"Assign", "Token name, std::shared_ptr<Expr> value"},
    }, Template(
            "Expr",
            "",
            true
    ));

    defineAst(outputDir, "Stmt", {
            {"Expression", "std::shared_ptr<Expr> expr"},
            {"Print", "std::shared_ptr<Expr> expr"},
            {"Var", "Token name, std::shared_ptr<Expr> initializer"},
            {"Block", "std::vector<std::shared_ptr<Stmt>> stmts"},
    }, Template(
            "Stmt",
            "#include \"./Expr.h\"\n"
    ));
}

void AstGenerator::defineAst(const std::string &outputDir, const std::string &baseName,
                             const std::map<std::string, std::string> &types, const Template& extra) {
    std::filesystem::path fullPath(outputDir);
    fullPath /= (baseName + ".h");
    auto str = fullPath.string();
    std::ofstream out(fullPath.string());
    // Macro definition
    out << extra.macro;

    // Includes
    out << "#include \"../interpreter/Scanner.h\"\n" << extra.include << "\n";

    // Base class definition
    out << "namespace Interpreter {\n    class " << baseName << " {";
    if (extra.visitReturned) {
        out << R"(
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
)";
    } else {
        out << R"(
    public:
        class Visitor;
        void accept(Visitor& visitor) {
            doAccept(visitor);
        };
        virtual void doAccept(Visitor& visitor) {}
)";
    }

    for (auto& type: types) {
        out << "        class " << type.first << ";\n";
    }

    out << "    };\n\n    class " << baseName << "::Visitor {\n    public:\n";

    for(auto& type: types) {
        out << "        virtual void visit" << type.first << baseName << "(" << type.first << "* expr) = 0;\n";
    }

    out << "    };\n\n";
    if (extra.visitReturned) {
        out << "    template <typename R>\n    class ";
        out << baseName << "::VisitorR: public " << baseName << "::Visitor {";

        out << R"(
    public:
        R result;
    };

)";
    }

    for (auto& type: types) {
        defineType(out, baseName, type.first, type.second);
    }

    out << "}\n\n#endif";

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
    out << "        void doAccept(Visitor& visitor) override {\n";
    out << "            visitor.visit" << className << baseName << "(this);";
    out << R"(
        };
    };

)";
}
