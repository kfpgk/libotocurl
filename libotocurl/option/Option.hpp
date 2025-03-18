#ifndef LIBOTOCURL_OPTION_OPTION_HPP
#define LIBOTOCURL_OPTION_OPTION_HPP

#include <libotocurl/wrapper/Easy.hpp>

#include <functional>

namespace otocurl::option {

    /**
     * @brief: Abstract wrapper for an arbitrary CURLOPT
     * 
     * @details
     * Patterns:
     *  - Command
     *  - Component & leaf of the composite pattern
     *  - Non virtual interface
     */
    class Option {

    public:
        /**
         * @brief Constructor
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set
         */
        Option(wrapper::Easy& curlInterface) noexcept;

        /**
         * @brief Virtual default destructor
         */
        virtual ~Option() = default;

        /**
         * @brief Reset the curl interface
         * 
         * @param[in] curlInterface The curl interface for which this option shall be set
         */
        void setInterface(wrapper::Easy& curlInterface) noexcept;

        /**
         * @brief Command method to set the specific command
         * 
         * @details Calls virtual function `doSet()`
         */
        void set();

    protected:
        /// @brief The curl interface for which this option shall be set
        std::reference_wrapper<wrapper::Easy> curlInterface; 

    private:
        /**
         * @brief Pure virtual command method to perform the actual setting of an option
         * 
         * Overriden in concrete commands (options)
         */
        virtual void doSet() = 0;

    };

}

#endif