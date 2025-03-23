#include <libotocurl/option/Verbose.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

namespace otocurl::option {

    Verbose::Verbose(wrapper::Easy& curlInterface, bool targetValue) :
        Option(curlInterface),
        targetValue{targetValue} {

        try {
            setCurrentValue(getActualValue());
        } catch (...) {
            /* Do nothing */
        }
    }

    Verbose::Verbose(wrapper::Easy& curlInterface, bool targetValue, bool resetValue) :
        Option(curlInterface),
        ResettableOption(resetValue),
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
            getInterface().setOption(curlOption, 1L);
        } else {
            getInterface().setOption(curlOption, 0L);
        }        
    }

    bool Verbose::getActualValue() const {
        auto value = std::any_cast<long>(getInterface().getOptionValue(curlOption));
        return value == 1L;
    }

}