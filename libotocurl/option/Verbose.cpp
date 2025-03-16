#include <libotocurl/option/Verbose.hpp>
#include <libotocurl/option/Option.hpp>

#include <curl/curl.h>

namespace otocurl::option {

    Verbose::Verbose(wrapper::Easy& curlInterface,
        bool value) :
        Option(curlInterface),
        value{value} {

    }

    Verbose::Verbose(wrapper::Easy& curlInterface,
        bool value,
        bool resetValue) :
        Option(curlInterface),
        value{value},
        ResettableOption(resetValue) {

    }

    Verbose::~Verbose() {
        reset();  
    }

    bool Verbose::getValue() const {
        return value;
    }

    void Verbose::setTo(bool value) {
        if (value) {
            curlInterface.get().setOption(CURLOPT_VERBOSE, 1L);
        } else {
            curlInterface.get().setOption(CURLOPT_VERBOSE, 0L);
        }        
    }

}