#include <libotocurl/option/Option.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

#include <tuple>
#include <type_traits>

namespace otocurl::option {

    /**
     * @brief Constructor that saves the variadic parameter pack
     * to a tuple for later usage.
     */
    template<typename... Args> 
    Generic<Args...>::Generic(wrapper::Easy& curlInterface,
        CURLoption curlOption, Args&&... args) :
            Option(curlInterface),
            curlOption{ curlOption },
            args{std::make_tuple(std::forward<Args>(args)...)} {

    }

    /**
     * @brief Calls generic setOption of a curl interface
     * 
     * Combine the previously saved variadic parameter pack
     * which is now available as a tuple with a lambda to
     * call the template setOption method of the interface.
     */
    template<typename... Args> 
    void Generic<Args...>::doSet() {
        auto optionAndArgs = std::tuple_cat(std::make_tuple(curlOption), args);
        std::apply([this](auto &&... args) 
            -> decltype(getInterface().setOption(std::forward<decltype(args)>(args)...))
            { 
                getInterface().setOption(std::forward<decltype(args)>(args)...);
            },
            optionAndArgs);
    }

}