#ifndef LIBOTOCURL_EXCEPTION_HPP
#define LIBOTOCURL_EXCEPTION_HPP

#include <string>
#include <optional>
#include <stdexcept>

namespace otocurl {

    class Exception : public std::runtime_error {

    public:
        Exception(const std::string& errorMessage);

    private:
        /**
         * @brief The complete error message including context
         * and error message.
         *
         * This is printed by what(). It is constructed during
         * what() which has to be const to conform to standard
         * prototype. This is why it is declared "mutable".
         *
         * This member is also the buffer for the const char*
         * that is being returned by what(). Must be valid
         * after returning from what().
         */
        mutable std::string completeErrorMessageBuffer;
        std::string errorMessage;

    };

}

#endif