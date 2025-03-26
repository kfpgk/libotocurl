#ifndef LIBOTOCURL_PARSER_STRING_OPERATIONS_HPP
#define LIBOTOCURL_PARSER_STRING_OPERATIONS_HPP

#include <string>

namespace otocurl::parser::string_operations {

	/*
	 * @brief Trim all white spaces from left and right of the input string
	 * 
	 * @param[in] input The string to be trimmed
	 * 
	 * @return A trimmed copy of the input string
	 */
	std::string trim(const std::string& input);

}

#endif