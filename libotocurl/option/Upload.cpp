#include <libotocurl/option/Upload.hpp>
#include <libotocurl/option/Option.hpp>

namespace otocurl::option {

    Upload::Upload(wrapper::Easy& curlInterface,
        bool value) :
            Option(curlInterface),
            value{value} {

    }

    Upload::Upload(wrapper::Easy& curlInterface,
        bool value,
        bool resetValue) :
            Option(curlInterface),
            value{value},
            ResettableOption(resetValue) {

    }

    Upload::~Upload() {
        reset();   
    }

    bool Upload::getValue() {
        return value;
    }

    void Upload::setTo(bool value) {
        if (value) {
            curlInterface.get().setOption(CURLOPT_UPLOAD, 1L);
        } else {
            curlInterface.get().setOption(CURLOPT_UPLOAD, 0L);
        }
        
    }

}