#ifndef LIBOTOCURL_OPTION_COLLECTION_HPP
#define LIBOTOCURL_OPTION_COLLECTION_HPP

#include <libotocurl/option/Option.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <memory>
#include <deque>

namespace otocurl::option {

    /**
     * @brief Collection of CURLOPTs
     * 
     * This collection can be used to conviniently pass a set of options around or
     * to set all included options at once.
     * 
     * The collection follows the composite pattern and hence allows to be treated
     * in the same way as a single `Option` object.
     * 
     * @details
     * Patterns:
     *  - Composite of the composite pattern
     */
    class Collection : public Option {

    public:
        /**
         * @brief Constructor
         * 
         * @param[in] curlInterface The curl interface for which all options will be set
         */
        explicit Collection(wrapper::Easy& curlInterface) noexcept;

        /**
         * @brief Add an option to the collection
         * 
         * @param[in] option The option to be added
         */
        void add(std::shared_ptr<Option> option);

        /**
         * @brief Remove all options from the collection
         */
        void clear();

    private:
        std::deque<std::shared_ptr<Option>> options; ///< Container for the options

        /**
         * @brief Perform the setting of all options that are included in the collection
         */
        virtual void doSet();

    };

}

#endif