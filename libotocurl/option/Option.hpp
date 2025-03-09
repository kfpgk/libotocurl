#ifndef LIBOTOCURL_OPTION_OPTION_HPP
#define LIBOTOCURL_OPTION_OPTION_HPP

#include <libotocurl/wrapper/Easy.hpp>

#include <functional>

namespace otocurl::option {

    /**
     * @brief: Abstract wrapper for an arbitrary CURLOPT
     * 
     * Patterns:
     *  - Command
     *  - Component & leaf of the composite pattern
     *  - Non virtual interface
     */
    class Option {

    public:
        Option(wrapper::Easy& curlInterface);
        virtual ~Option() = default;
        void setEasy(wrapper::Easy& curlInterface);

        void set();

    protected:
        std::reference_wrapper<wrapper::Easy> curlInterface;

    private:
        virtual void doSet() = 0;

    };

}

#endif