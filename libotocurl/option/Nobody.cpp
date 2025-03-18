#include <libotocurl/option/Nobody.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

namespace otocurl::option {

    Nobody::Nobody(wrapper::Easy& curlInterface, bool targetValue) noexcept :
        Option(curlInterface),
        targetValue{targetValue} {

    }

    Nobody::Nobody(wrapper::Easy& curlInterface, bool targetValue, bool resetValue) noexcept:
        Option(curlInterface),
        targetValue{targetValue},
        ResettableOption(resetValue) {

    }

    Nobody::~Nobody() {
        reset();
    }

    bool Nobody::getTargetValue() const {
        return targetValue;
    }

    void Nobody::setTo(bool targetValue) {
        if (targetValue) {
            curlInterface.get().setOption(CURLOPT_NOBODY, 1L);
        } else {
            curlInterface.get().setOption(CURLOPT_NOBODY, 0L);
        }        
    }

}