#include <libotocurl/wrapper/Exception.hpp>

#include <sstream>

namespace otocurl::wrapper {

    Exception::Exception(const std::string& errorMessage) :
        std::runtime_error(errorMessage) {

    }

    Exception::Exception(
        const std::string& errorMessage,
        CURLcode curlCode) :
        std::runtime_error(errorMessage),
        curlCode{ curlCode } {

        std::stringstream message;
        message << errorMessage << std::endl;
        message << getCurlUCodeMessage() << std::endl;
        this->errorMessage = message.str();
    }

    Exception::Exception(
        const std::string& errorMessage,
        CURLcode curlCode,
        const char* curlErrorBuffer) :
            std::runtime_error(errorMessage),
            curlCode{ curlCode },
            curlErrorBuffer{curlErrorBuffer} {

        std::stringstream message;
        message << errorMessage << std::endl;
        message << getCurlCodeMessage() << std::endl;
        message << getCurlErrorBufferMessage() << std::endl;
        this->errorMessage = message.str();  
    }

    Exception::Exception(
        const std::string& errorMessage,
        CURLUcode curlUCode) :
        std::runtime_error(errorMessage),
        curlUCode{ curlUCode } {

        std::stringstream message;
        message << errorMessage << std::endl;
        message << getCurlUCodeMessage() << std::endl;
        this->errorMessage = message.str();
    }

    CURLcode Exception::getCurlCode() const {
        return curlCode;
    }

    CURLUcode Exception::getCurlUCode() const {
        return curlUCode;
    }

    std::string Exception::getCurlCodeMessage() const {
        std::stringstream message;
        std::string curlCodeErrorString = std::string(curl_easy_strerror(curlCode));
        message << "CURLcode[" << curlCode << "]: '" \
            << curlCodeErrorString << "'";
        return message.str();
    }

    std::string Exception::getCurlUCodeMessage() const {
        std::stringstream message;
        std::string curlUCodeErrorString = std::string(curl_url_strerror(curlUCode));
        message << "CURLUcode[" << curlUCode << "]: '" \
            << curlUCodeErrorString << "'";
        return message.str();
    }

    std::string Exception::getCurlErrorBufferMessage() const {
        std::stringstream message;
        if (!curlErrorBuffer.empty()) {
            message << "CURL ERRORBUFFER: '" << curlErrorBuffer << "'";
        }
        return message.str();
    }

}