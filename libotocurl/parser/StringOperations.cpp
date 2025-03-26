#include <libotocurl/parser/StringOperations.hpp>

#include <regex>
#include <string>

namespace otocurl::parser::string_operations {

    std::string trim(const std::string& input) {
        return std::regex_replace(input, std::regex("(^[ \n\r]+)|([ \n\r]+$)"), "");
    }

}