#include <libotocurl/option/OptionStub.test.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>

namespace otocurl::option::unit_test {

    OptionStub::OptionStub(bool targetValue) noexcept :
        Option(easyStub),
        targetValue{targetValue} {

    }

    OptionStub::OptionStub(bool targetValue, bool resetValue) noexcept:
        Option(easyStub),
        targetValue{targetValue},
        ResettableOption(resetValue) {

    }

    OptionStub::~OptionStub() {
        reset();
    }

    bool OptionStub::getTargetValue() const {
        return targetValue;
    }

    bool OptionStub::getCURLOPTvalue() const {
        return stubbedCURLOPTvalue;
    }

    void OptionStub::setTo(bool targetValue) {
        stubbedCURLOPTvalue = targetValue;       
    }

}