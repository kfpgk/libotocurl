#include <libotocurl/option/Verbose.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

#include <functional>

namespace otocurl::option {

    Verbose::Verbose(wrapper::Easy& curlInterface, bool targetValue) :
        curlInterface{ curlInterface },
        targetValue{targetValue} {

        try {
            setCurrentValue(getActualValue());
        } catch (...) {
            /* Do nothing */
        }
    }

    Verbose::Verbose(wrapper::Easy& curlInterface, bool targetValue, bool resetValue) :
        ResettableOption(resetValue),
        curlInterface{ curlInterface },
        targetValue{targetValue} {

        try {
            setCurrentValue(getActualValue());
        } catch (...) {
            /* Do nothing */
        }
    }

    Verbose::~Verbose() {
        reset();  
    }

    bool Verbose::getTargetValue() const {
        return targetValue;
    }

    void Verbose::setTo(bool targetValue) {
        if (targetValue) {
            curlInterface.get().setOption(curlOption, 1L);
        } else {
            curlInterface.get().setOption(curlOption, 0L);
        }        
    }

    bool Verbose::getActualValue() const {
        auto value = std::any_cast<long>(curlInterface.get().getOptionValue(curlOption));
        return value == 1L;
    }

}