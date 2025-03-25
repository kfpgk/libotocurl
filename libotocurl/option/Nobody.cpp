#include <libotocurl/option/Nobody.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

#include <functional>

namespace otocurl::option {

    Nobody::Nobody(wrapper::Easy& curlInterface, bool targetValue) noexcept :
        curlInterface{ curlInterface },
        targetValue{targetValue} {

        try {
            setCurrentValue(getActualValue());
		} catch (...) {
            /* Do nothing */
        }
    }

    Nobody::Nobody(wrapper::Easy& curlInterface, bool targetValue, bool resetValue) noexcept:
        ResettableOption(resetValue),
        curlInterface{ curlInterface },
        targetValue{targetValue} {

        try {
            setCurrentValue(getActualValue());
        } catch (...) {
            /* Do nothing */
        }
    }

    Nobody::~Nobody() {
        reset();
    }

    bool Nobody::getTargetValue() const {
        return targetValue;
    }

    void Nobody::setTo(bool targetValue) {
        if (targetValue) {
            curlInterface.get().setOption(curlOption, 1L);
        } else {
            curlInterface.get().setOption(curlOption, 0L);
        }        
    }

    bool Nobody::getActualValue() const {
        auto value = std::any_cast<long>(curlInterface.get().getOptionValue(curlOption));
        return value == 1L;
    }

}