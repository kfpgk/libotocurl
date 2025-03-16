#include <libotocurl/option/Nobody.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <curl/curl.h>

namespace otocurl::option {

    Nobody::Nobody(wrapper::Easy& curlInterface, bool value) noexcept :
        Option(curlInterface),
        value{value} {

    }

    Nobody::Nobody(wrapper::Easy& curlInterface, bool value, bool resetValue) noexcept:
        Option(curlInterface),
        value{value},
        ResettableOption(resetValue) {

    }

    Nobody::~Nobody() {
        reset();
    }

    bool Nobody::getValue() const {
        return value;
    }

    void Nobody::setTo(bool value) {
        if (value) {
            curlInterface.get().setOption(CURLOPT_NOBODY, 1L);
        } else {
            curlInterface.get().setOption(CURLOPT_NOBODY, 0L);
        }        
    }

}