#include <libotocurl/option/Factory.hpp>

#include <memory>

namespace filesync::curl::option {

    Factory::Factory(wrapper::Easy& curlInterface) :
        curlInterface{ curlInterface } {

    }

    std::unique_ptr<Collection> Factory::createCollection() const {
        return std::make_unique<Collection>(curlInterface);
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

    std::unique_ptr<Quote> Factory::createQuote(
        const std::string& command) const {

        return std::make_unique<Quote>(curlInterface, command);
    }

    std::unique_ptr<Quote> Factory::createVolatileQuote() const {

        return std::make_unique<Quote>(curlInterface, "", nullptr);
    }

    std::unique_ptr<Quote> Factory::createVolatileQuote(
        const std::string& command) const {

        return std::make_unique<Quote>(curlInterface, command, nullptr);
    }

    std::unique_ptr<Upload> Factory::createUpload(
        bool value) const {
        
        return std::make_unique<Upload>(curlInterface, value);
    }

    std::unique_ptr<Upload> Factory::createVolatileUpload(
        bool value) const {
        
        return std::make_unique<Upload>(curlInterface, value, false);
    }

    std::unique_ptr<Verbose> Factory::createVerbose() const {
        return std::make_unique<Verbose>(curlInterface, true);
    }

    std::unique_ptr<Verbose> Factory::createVolatileVerbose() const {
        return std::make_unique<Verbose>(curlInterface, true, false);
    }

}