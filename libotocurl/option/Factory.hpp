#ifndef LIBFILESYNC_CURL_OPTION_FACTORY_HPP
#define LIBFILESYNC_CURL_OPTION_FACTORY_HPP

#include <libotocurl/wrapper/Easy.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/Collection.hpp>
#include <libotocurl/option/Generic.hpp>
#include <libotocurl/option/Nobody.hpp>
#include <libotocurl/option/Upload.hpp>
#include <libotocurl/option/Quote.hpp>
#include <libotocurl/option/Verbose.hpp>

#include <curl/curl.h>

namespace filesync::curl::option {

    class Factory {

    public:
        explicit Factory(wrapper::Easy& curlInterface);

        template <typename... Args>
        [[nodiscard]] std::unique_ptr<Option> createGeneric(CURLoption curlOption, Args&&... args) const;

        [[nodiscard]] std::unique_ptr<Collection> createCollection() const;

        [[nodiscard]] std::unique_ptr<Nobody> createNobody() const;
        [[nodiscard]] std::unique_ptr<Nobody> createVolatileNobody() const;

        [[nodiscard]] std::unique_ptr<Quote> createQuote() const;
        [[nodiscard]] std::unique_ptr<Quote> createQuote(const std::string& command) const;
        [[nodiscard]] std::unique_ptr<Quote> createVolatileQuote() const;
        [[nodiscard]] std::unique_ptr<Quote> createVolatileQuote(const std::string& command) const;

        [[nodiscard]] std::unique_ptr<Upload> createUpload(bool value) const;
        [[nodiscard]] std::unique_ptr<Upload> createVolatileUpload(bool value) const;

        [[nodiscard]] std::unique_ptr<Verbose> createVerbose() const;
        [[nodiscard]] std::unique_ptr<Verbose> createVolatileVerbose() const;

    private:
        wrapper::Easy& curlInterface;

    };

}

#include <libotocurl/option/Factory.tpp>

#endif