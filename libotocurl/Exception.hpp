#ifndef LIBFILESYNC_CURL_EXCEPTION_HPP
#define LIBFILESYNC_CURL_EXCEPTION_HPP

#include <curl/curl.h>

#include <string>
#include <optional>
#include <stdexcept>

namespace filesync::curl {

    class Exception : public std::runtime_error {

        public:
            Exception(const std::string& errorMessage);
            Exception(const std::string& errorMessage,
                CURLcode curlCode);
            Exception(const std::string& errorMessage,
                CURLcode curlCode,
                const char* curlErrorBuffer);
            Exception(const std::string& errorMessage,
                CURLUcode curlUCode);

            CURLcode getCurlCode() const;
            CURLUcode getCurlUCode() const;

        private:
            std::string curlErrorBuffer;
            CURLcode curlCode = CURLE_OK;
            CURLUcode curlUCode = CURLUE_OK;
            std::string getCurlCodeMessage() const;
            std::string getCurlUCodeMessage() const;
            std::string getCurlErrorBufferMessage() const;

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