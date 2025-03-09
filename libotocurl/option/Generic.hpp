#ifndef LIBFILESYNC_CURL_OPTION_GENERIC_HPP
#define LIBFILESYNC_CURL_OPTION_GENERIC_HPP

#include <libotocurl/option/Option.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

#include <tuple>
		
namespace filesync::curl::option {

    /**
     * @brief Generic CURLOPT class usable for every
     * CURLOPT option.
     * 
     * Use this if there is no specific CURLOPT class
     * available.
     */
    template<typename... Args> 
    class Generic : public Option {

    public:
        Generic(wrapper::Easy& curlInterface,
            CURLoption curlOption, Args&&... args);

    private:
        CURLoption curlOption;
        /**
            * @brief Storage for variadic template arguments
            * 
            * Decay the types, because we cannot store some
            * const literal types (e.g. const char[N]) in 
            * a member. 
            */
        std::tuple<std::decay_t<Args>...> args;

        void doSet() override;

    };

}

#include <libotocurl/option/Generic.tpp>

#endif