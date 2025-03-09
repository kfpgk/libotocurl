#ifndef LIBOTOCURL_OPTION_RESETTABLE_OPTION_HPP
#define LIBOTOCURL_OPTION_RESETTABLE_OPTION_HPP

#include <libotocurl/option/Option.hpp>

#include <optional>

namespace otocurl::option {

    /**
     * @brief CURLOPT that provides an interface
     * for resetting the option.
     */
    template<typename T> 
    class ResettableOption : virtual public Option {

        public:
            ResettableOption() = default;
            explicit ResettableOption(const T& resetValue);
            virtual ~ResettableOption() = default;

            void reset();

        private:
            std::optional<T> resetValue;

            virtual void setTo(T value) = 0;

    };

}

#include <libotocurl/option/ResettableOption.tpp>

#endif