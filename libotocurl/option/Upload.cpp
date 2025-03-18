#include <libotocurl/option/Upload.hpp>
#include <libotocurl/option/Option.hpp>

namespace otocurl::option {

    Upload::Upload(wrapper::Easy& curlInterface,
        bool targetValue) :
            Option(curlInterface),
            targetValue{targetValue} {

    }

    Upload::Upload(wrapper::Easy& curlInterface,
        bool targetValue,
        bool resetValue) :
            Option(curlInterface),
            targetValue{targetValue},
            ResettableOption(resetValue) {

    }

    Upload::~Upload() {
        reset();   
    }

    bool Upload::getTargetValue() const {
        return targetValue;
    }

    void Upload::setTo(bool targetValue) {
        if (targetValue) {
            curlInterface.get().setOption(CURLOPT_UPLOAD, 1L);
        } else {
            curlInterface.get().setOption(CURLOPT_UPLOAD, 0L);
        }
        
    }

}