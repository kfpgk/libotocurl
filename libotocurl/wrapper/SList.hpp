#ifndef LIBOTOCURL_WRAPPER_SLIST_HPP
#define LIBOTOCURL_WRAPPER_SLIST_HPP

#include <libotocurl/wrapper/Base.hpp>

#include <curl/curl.h>

#include <string>
#include <string_view>
#include <vector>

namespace otocurl::wrapper {

    /**
     * @brief Wrapper for curl_slist
     */
    class SList : public Base {

        public:
            SList() = default;
            SList(const std::string& content);
            ~SList();
            SList(const SList&);
            SList(SList&& rhs);
            SList& operator=(SList);
            friend void swap(SList& lhs, SList& rhs);

            [[nodiscard]] bool isEmpty() const;
            [[nodiscard]] curl_slist* getSListPointer() const;

            void append(const std::string_view content);

        private:
            curl_slist* handle = NULL;
            std::vector<std::string> contents;

    };

}

#endif