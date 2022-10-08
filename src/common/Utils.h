//
// Created by pikay on 2022/10/3.
//

#ifndef CPPLOX_UTILS_H
#define CPPLOX_UTILS_H

#include <memory>
#include <string>
#include <stdexcept>
#include <vector>
#include <sstream>
#include <any>

namespace Common {
    // source: https://stackoverflow.com/a/26221725
    template<typename ... Args>
    std::string string_format( const std::string& format, Args ... args );

    // source: https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
    std::string ltrim(const std::string &s);
    std::string rtrim(const std::string &s);
    std::string trim(const std::string &s);

    // source: https://stackoverflow.com/a/46931770
    std::vector<std::string> split (const std::string &s, char delim);

    // for std::any related check
    template<typename T>
    bool checkValueType(const std::any &value, T &target) {
        if (const T *p = std::any_cast<T>(&value)) {
            target = *p;
            return true;
        }
        return false;
    }

    std::string stringify(const std::any& value);
}

#endif //CPPLOX_UTILS_H
