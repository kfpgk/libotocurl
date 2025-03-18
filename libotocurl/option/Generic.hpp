#ifndef LIBOTOCURL_OPTION_GENERIC_HPP
#define LIBOTOCURL_OPTION_GENERIC_HPP

#include <libotocurl/option/Option.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

#include <tuple>
#include <type_traits>
		
namespace otocurl::option {

    /**
     * @brief Generic CURLOPT class usable for every CURLOPT option.
     * 
     * Use this if there is no specific CURLOPT class available. This class does not provide
     * undo, redo or reset functionality.
     * 
     * @details
     * Patterns:
     *  - Command
     */
    template<typename... Args> 
    class Generic : public Option {

    public:
        /**
         * @brief Constructor
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set 
         * @param[in] curlOption The CURLOPT that shall be set
         * @param[in] args Variadic parameter list depending on \p curlOption
         */
        Generic(wrapper::Easy& curlInterface, CURLoption curlOption, Args&&... args);

    private:
        CURLoption curlOption; ///< The CURLOPT that shall be set

        /**
         * @brief Storage for variadic template arguments
         * 
         * Decay the types, because we cannot store some
         * const literal types (e.g. const char[N]) in a member. 
         */
        std::tuple<std::decay_t<Args>...> args;

        /**
         * @brief Perform command to set the CURLOPT to the given value
         */
        void doSet() override;

    };

}

#include <libotocurl/option/Generic.tpp>

#endif