//
// Created by pikay on 2022/10/5.
//


#include "Utils.h"

namespace Common {
    // source: https://stackoverflow.com/a/26221725
    template<typename ... Args>
    std::string string_format( const std::string& format, Args ... args )
    {
        int size_s = std::snprintf( nullptr, 0, format.c_str(), args ... ) + 1; // Extra space for '\0'
        if( size_s <= 0 ){ throw std::runtime_error( "Error during formatting string." ); }
        auto size = static_cast<size_t>( size_s );
        std::unique_ptr<char[]> buf( new char[ size ] );
        std::snprintf( buf.get(), size, format.c_str(), args ... );
        return std::string( buf.get(), buf.get() + size - 1 ); // We don't want the '\0' inside
    }

    // source: https://www.techiedelight.com/trim-string-cpp-remove-leading-trailing-spaces/
    std::string ltrim(const std::string &s)
    {
        size_t start = s.find_first_not_of(" \n\r\t\f\v");
        return (start == std::string::npos) ? "" : s.substr(start);
    }

    std::string rtrim(const std::string &s)
    {
        size_t end = s.find_last_not_of(" \n\r\t\f\v");
        return (end == std::string::npos) ? "" : s.substr(0, end + 1);
    }

    std::string trim(const std::string &s) {
        return rtrim(ltrim(s));
    }

    // source: https://stackoverflow.com/a/46931770
    std::vector<std::string> split (const std::string &s, char delim) {
        std::vector<std::string> result;
        std::stringstream ss (s);
        std::string item;

        while (getline (ss, item, delim)) {
            result.push_back (trim(item));
        }

        return result;
    }

    std::string stringify(const std::any &value) {
        if (!value.has_value()) {
            return "nil";
        }
        if (const auto* p = std::any_cast<double>(&value)) {
            auto text = std::to_string(*p);
            return text;
        } else if (const auto* p = std::any_cast<std::string>(&value)) {
            return *p;
        }

        return "nan";
    }
}