#ifndef LIBOTOCURL_OPTION_RESETTABLE_OPTION_HPP
#define LIBOTOCURL_OPTION_RESETTABLE_OPTION_HPP

#include <libotocurl/option/Option.hpp>

#include <optional>

namespace otocurl::option {

    /**
     * @brief Implementation of a CURLOPT that supports reset functionality
     */
    template<typename T> 
    class ResettableOption : virtual public Option {

    public:
        /**
         * @brief Default constructor
         */
        ResettableOption() = default;

        /**
         * @brief Constructor
         * 
         * @param[in] resetValue The value to which the option is reset to on 
         * destruction of this object
         */
        explicit ResettableOption(const T& resetValue);

        /**
         * @brief Default virtual destructor
         * 
         * Object may be deleted through derived pointer
         */
        virtual ~ResettableOption() = default;

        /**
         * @brief Reset the option to the stored reset value if available
         * 
         * Noop if reset value is not available
         */
        void reset();

    private:
        std::optional<T> resetValue; ///< Holds reset value if available

        /**
         * @brief Pure virtual method to set an option to a specific value
         * 
         * A concrete `Option` object must provide this method to be resettable
         * 
         * @param[in] value The value that is being set
         */
        virtual void setTo(T value) = 0;

    };

}

#include <libotocurl/option/ResettableOption.tpp>

#endif