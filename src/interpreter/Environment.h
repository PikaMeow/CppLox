//
// Created by pikay on 2022/10/11.
//

#ifndef CPPLOX_ENVIRONMENT_H
#define CPPLOX_ENVIRONMENT_H

#include <map>
#include <string>
#include <any>
#include "CppLoxErrorHandler.h"

namespace Interpreter {
    class Environment {
    private:
        std::map<std::string, std::any> container;
        std::shared_ptr<Environment> enclosing;

    public:
        Environment() {
            enclosing = nullptr;
        }

        Environment(std::shared_ptr<Environment> enclosing): enclosing(enclosing) {}

        std::any get(const Token& name) {
            if (container.find(name.lexeme) != container.end()) {
                return container[name.lexeme];
            }
            if (enclosing != nullptr) {
                return enclosing->get(name);
            }
            throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
        }

        void put(const std::string& name, const std::any& value) {
            container[name] = value;
        }

        void assign(const Token& name, const std::any& value) {
            if (container.find(name.lexeme) != container.end()) {
                put(name.lexeme, value);
                return;
            }
            if (enclosing != nullptr) {
                enclosing->assign(name, value);
                return;
            }
            throw RuntimeError(name, "Undefined variable '" + name.lexeme + "'.");
        }
    };
}

#endif //CPPLOX_ENVIRONMENT_H
