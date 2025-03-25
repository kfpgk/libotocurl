#include <libotocurl/option/Factory.hpp>
#include <libotocurl/option/Collection.hpp>
#include <libotocurl/option/Generic.hpp>
#include <libotocurl/option/Nobody.hpp>
#include <libotocurl/option/Upload.hpp>
#include <libotocurl/option/Quote.hpp>
#include <libotocurl/option/Verbose.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <memory>

namespace otocurl::option {

    Factory::Factory(wrapper::Easy& curlInterface) noexcept :
        curlInterface{ curlInterface } {

    }

    std::unique_ptr<Collection> Factory::createCollection() const {
        return std::make_unique<Collection>();
    }

    std::unique_ptr<Nobody> Factory::createNobody() const {
        return std::make_unique<Nobody>(curlInterface, true);
    }

    std::unique_ptr<Nobody> Factory::createVolatileNobody() const {
        return std::make_unique<Nobody>(curlInterface, true, false);
    }

    std::unique_ptr<Quote> Factory::createQuote() const {
        return std::make_unique<Quote>(curlInterface, "");
    }

    std::unique_ptr<Quote> Factory::createQuote(const std::string& command) const {
        return std::make_unique<Quote>(curlInterface, command);
    }

    std::unique_ptr<Quote> Factory::createVolatileQuote() const {

        return std::make_unique<Quote>(curlInterface, "", nullptr);
    }

    std::unique_ptr<Quote> Factory::createVolatileQuote(const std::string& command) const {
        return std::make_unique<Quote>(curlInterface, command, nullptr);
    }

    std::unique_ptr<Upload> Factory::createUpload(bool targetValue) const {
        return std::make_unique<Upload>(curlInterface, targetValue);
    }

    std::unique_ptr<Upload> Factory::createVolatileUpload(bool targetValue) const {
        return std::make_unique<Upload>(curlInterface, targetValue, false);
    }

    std::unique_ptr<Verbose> Factory::createVerbose() const {
        return std::make_unique<Verbose>(curlInterface, true);
    }

    std::unique_ptr<Verbose> Factory::createVolatileVerbose() const {
        return std::make_unique<Verbose>(curlInterface, true, false);
    }

}