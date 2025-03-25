#include <libotocurl/option/Upload.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/wrapper/Easy.hpp>

#include <functional>

namespace otocurl::option {

    Upload::Upload(wrapper::Easy& curlInterface, bool targetValue) :
        curlInterface{ curlInterface },
        targetValue{targetValue} {

        try {
            setCurrentValue(getActualValue());
        } catch (...) {
            /* Do nothing */
        }
    }

    Upload::Upload(wrapper::Easy& curlInterface, bool targetValue, bool resetValue) :
        ResettableOption(resetValue),
        curlInterface{ curlInterface },
        targetValue{targetValue} {

        try {
            setCurrentValue(getActualValue());
        } catch (...) {
            /* Do nothing */
        }
    }

    Upload::~Upload() {
        reset();   
    }

    bool Upload::getTargetValue() const {
        return targetValue;
    }

    void Upload::setTo(bool targetValue) {
        if (targetValue) {
            curlInterface.get().setOption(curlOption, 1L);
        } else {
            curlInterface.get().setOption(curlOption, 0L);
        }
    }

    bool Upload::getActualValue() const {
        auto value = std::any_cast<long>(curlInterface.get().getOptionValue(curlOption));
        return value == 1L;
    }

}