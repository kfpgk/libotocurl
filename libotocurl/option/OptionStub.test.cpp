#include <libotocurl/option/OptionStub.test.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>

namespace otocurl::option::unit_test {

    OptionStub::OptionStub(bool value) noexcept :
        Option(easyStub),
        value{value} {

    }

    OptionStub::OptionStub(bool value, bool resetValue) noexcept:
        Option(easyStub),
        value{value},
        ResettableOption(resetValue) {

    }

    OptionStub::~OptionStub() {
        reset();
    }

    bool OptionStub::getValue() const {
        return value;
    }

    bool OptionStub::getCURLOPTvalue() const {
        return stubbedCURLOPTvalue;
    }

    void OptionStub::setTo(bool value) {
        stubbedCURLOPTvalue = value;       
    }

}