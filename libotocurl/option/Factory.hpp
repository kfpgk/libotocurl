#ifndef LIBOTOCURL_OPTION_FACTORY_HPP
#define LIBOTOCURL_OPTION_FACTORY_HPP

#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/Collection.hpp>
#include <libotocurl/option/Generic.hpp>
#include <libotocurl/option/Nobody.hpp>
#include <libotocurl/option/Upload.hpp>
#include <libotocurl/option/Quote.hpp>
#include <libotocurl/option/Verbose.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

#include <memory>

namespace otocurl::option {

    /**
     * @brief Option factory for CURLOPTs
     * 
     * This is a simple factory that provides a collection of `create...()` methods 
     * and forwards the included curl interface
     */
    class Factory {

    public:
        /**
         * @brief Constructor
         * 
         * @param[in] curlInterface The curl interface which is being forwarded to 
         * all created `Option` objects
         */
        explicit Factory(wrapper::Easy& curlInterface) noexcept;

        /**
         * @brief Create a generic curl option
         * 
         * @param[in] curlOption The CURLOPT identifier
         * @param[in] args Target value. Type depends on \p curlOption
         */
        template <typename... Args>
        [[nodiscard]] std::unique_ptr<Option> createGeneric(
            CURLoption curlOption, Args&&... args) const;

        /**
         * @brief Create a collection of curl options into which multiple curl options can be
         * grouped together
         */
        [[nodiscard]] std::unique_ptr<Collection> createCollection() const;

        /**
         * @brief Create a persistent CURLOPT_NOBODY option 
         * 
         * The option does not get reset to default upon going out of scope
         */
        [[nodiscard]] std::unique_ptr<Nobody> createNobody() const;

        /**
         * @brief Create a volatile CURLOPT_NOBODY option 
         * 
         * The option will get reset to default upon going out of scope
         */
        [[nodiscard]] std::unique_ptr<Nobody> createVolatileNobody() const;

        /**
         * @brief Create a persistent CURLOPT_QUOTE with an empty command list 
         * 
         * The option does not get reset to default upon going out of scope
         */
        [[nodiscard]] std::unique_ptr<Quote> createQuote() const;

        /**
         * @brief Create a CURLOPT_QUOTE and add \p command to command list
         * 
         * The option does not get reset to default upon going out of scope
         * 
         * @param[in] command The command that is being added to the CURLOPT_QUOTE object 
         */
        [[nodiscard]] std::unique_ptr<Quote> createQuote(const std::string& command) const;

        /**
         * @brief Create a volatile CURLOPT_QUOTE with an empty command list 
         * 
         * The option will get reset to default upon going out of scope
         */
        [[nodiscard]] std::unique_ptr<Quote> createVolatileQuote() const;

        /**
         * @brief Create a volatile CURLOPT_QUOTE add \p command to command list
         * 
         * The option will get reset to default upon going out of scope
         * 
         * @param[in] command The command that is being added to the CURLOPT_QUOTE object
         */
        [[nodiscard]] std::unique_ptr<Quote> createVolatileQuote(const std::string& command) const;

       /**
         * @brief Create a persistent CURLOPT_UPLOAD option with target value \p targetValue 
         * 
         * The option does not get reset to default upon going out of scope
         * 
         * @param[in] targetValue Target value of the CURLOPT_UPLOAD option
         */
        [[nodiscard]] std::unique_ptr<Upload> createUpload(bool targetValue) const;

        /**
         * @brief Create a volatile CURLOPT_UPLOAD option with target value \p targetValue 
         * 
         * The option will get reset to default upon going out of scope
         * 
         * @param[in] targetValue Target value of the CURLOPT_UPLOAD option
         */
        [[nodiscard]] std::unique_ptr<Upload> createVolatileUpload(bool targetValue) const;

        /**
         * @brief Create a persistent CURLOPT_VERBOSE option that enables verbosity
         * 
         * The option does not get reset to default upon going out of scope
         */
        [[nodiscard]] std::unique_ptr<Verbose> createVerbose() const;

        /**
         * @brief Create a volatile CURLOPT_VERBOSE option that enables verbosity
         * 
         * The option will get reset to default upon going out of scope
         */
        [[nodiscard]] std::unique_ptr<Verbose> createVolatileVerbose() const;

    private:
        /// @brief The curl interface instance that is being given to all options 
        /// created by this factory
        wrapper::Easy& curlInterface; 

    };

}

#include <libotocurl/option/Factory.tpp>

#endif