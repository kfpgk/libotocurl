#include <libotocurl/option/Verbose.hpp>
#include <libotocurl/option/Option.hpp>

#include <curl/curl.h>

namespace otocurl::option {

    Verbose::Verbose(wrapper::Easy& curlInterface,
        bool targetValue) :
        Option(curlInterface),
        targetValue{targetValue} {

    }

    Verbose::Verbose(wrapper::Easy& curlInterface,
        bool targetValue,
        bool resetValue) :
        Option(curlInterface),
        targetValue{targetValue},
        ResettableOption(resetValue) {

    }

    Verbose::~Verbose() {
        reset();  
    }

    bool Verbose::getTargetValue() const {
        return targetValue;
    }

    void Verbose::setTo(bool targetValue) {
        if (targetValue) {
            curlInterface.get().setOption(CURLOPT_VERBOSE, 1L);
        } else {
            curlInterface.get().setOption(CURLOPT_VERBOSE, 0L);
        }        
    }

}