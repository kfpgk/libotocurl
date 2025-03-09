#include <libotocurl/option/Nobody.hpp>
#include <libotocurl/option/Option.hpp>

#include <curl/curl.h>

namespace filesync::curl::option {

    Nobody::Nobody(wrapper::Easy& curlInterface,
        bool value) :
            Option(curlInterface),
            value{value} {

    }

    Nobody::Nobody(wrapper::Easy& curlInterface,
        bool value,
        bool resetValue) :
            Option(curlInterface),
            value{value},
            ResettableOption(resetValue) {

    }

    Nobody::~Nobody() {
        reset();
    }

    bool Nobody::getValue() {
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