#ifndef LIBOTOCURL_WRAPPER_URL_HPP
#define LIBOTOCURL_WRAPPER_URL_HPP

#include <libotocurl/wrapper/Base.hpp>

#include <curl/curl.h>

#include <filesystem>
#include <string>

namespace otocurl::wrapper {

    /**
     * @brief Wrapper for curl_url
     */
    class Url : public Base {

        public:
            Url();
            ~Url();
            Url(const Url& rhs);
            Url(Url&& rhs) noexcept;
            Url& operator=(Url rhs);
            friend void swap(Url& lhs, Url& rhs);

            [[nodiscard]] char* getUrl();
            [[nodiscard]] char* getHost();
            [[nodiscard]] char* getScheme();
            [[nodiscard]] char* getPath();

            void setHost(const std::string& host);
            void setScheme(const std::string& scheme);
            void setPath(const std::string& path);
            void validate();           

        private:
            CURLU *handle;
            char* urlPointer = nullptr;

            template<typename... Args> 
            void setPart(CURLUPart part, Args&&... args);

    };

}

#include <libotocurl/wrapper/Url.tpp>

#endif