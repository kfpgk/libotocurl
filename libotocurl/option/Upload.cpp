#include <libotocurl/option/Upload.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/wrapper/Easy.hpp>

namespace otocurl::option {

    Upload::Upload(wrapper::Easy& curlInterface, bool targetValue) :
        Option(curlInterface),
        targetValue{targetValue} {

        try {
            setCurrentValue(getActualValue());
        } catch (...) {
            /* Do nothing */
        }
    }

    Upload::Upload(wrapper::Easy& curlInterface, bool targetValue, bool resetValue) :
        Option(curlInterface),
        ResettableOption(resetValue),
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
            getInterface().setOption(curlOption, 1L);
        } else {
            getInterface().setOption(curlOption, 0L);
        }
    }

    bool Upload::getActualValue() const {
        auto value = std::any_cast<long>(getInterface().getOptionValue(curlOption));
        return value == 1L;
    }

}