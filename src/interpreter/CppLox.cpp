//
// Created by pikay on 2022/9/29.
//

#include "CppLox.h"
#include "Parser.h"
#include "Interpreter.h"

namespace Interpreter {
    void CppLox::runCore(std::string code) {
        Scanner scanner(code);
        auto tokenList = scanner.Scan();

        Parser parser(tokenList);
        auto astTree = parser.Parse();

        if (hasError) return;

//        AstPrinter printer;
//        std::cout << printer.print(*astTree) << std::endl;

        Interpreter interpreter(astTree);
        interpreter.Interpret();
    }

    void CppLox::run(std::vector<std::string> &params) {
        if (params.empty()) {
            runPrompt();
        } else if (params.size() == 1) {
            runFile(params[0]);
        } else {
            throw new std::exception();
        }
    }

    void CppLox::runFile(std::string &filePath) {
        std::ifstream inputFile(filePath);
        std::stringstream buffer;
        buffer << inputFile.rdbuf();
        runCore(buffer.str());

        if (hasError) exit(65);
    }

    void CppLox::runPrompt() {
        hasError = false;
    }

    void CppLox::testAst() {
        // 1  + ( - 3 ) == true
        Token token1 = { NUMBER, "1", 1, 1};
        Token token2 = { ADD, "+", 1, NULL};
        Token token3 = { LEFT_PAREN, "(", 1, NULL};
        Token token4 = { SUB, "-", 1, NULL};
        Token token5 = { NUMBER, "3", 1, 3};
        Token token6 = { RIGHT_PAREN, ")", 1, NULL};
        Token token7 = { EE, "==", 1, NULL};
        Token token8 = {TRUE, "true", 1, NULL};

//        Expr::Literal literal1(token1);
//        Expr::Literal literal2(token5);
//        Expr::Literal literal3(token8);

//        Expr::Unary unary1(token4, literal2);
//        Expr::Grouping group1(unary1);
//        Expr::Binary binary1(literal1, token2, group1);
//        Expr::Binary binary2(binary1, token7, literal3);
//
//        AstPrinter printer;
//        std::cout << printer.print(binary2) << std::endl;
    }
} // Interpreter