#include <libotocurl/option/OptionStub.test.hpp>
#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/ResettableOption.hpp>
#include <libotocurl/option/UndoableOptionImpl.hpp>

namespace otocurl::option::unit_test {

    template<typename T>
    OptionStub<T>::OptionStub(T targetValue, T initialValue) noexcept :
        UndoableOptionImpl<T>(initialValue),
        targetValue{ targetValue },
        stubbedCURLOPTvalue{ initialValue } {

    }

    template<typename T>
    OptionStub<T>::OptionStub(T targetValue, T initialValue, T resetValue) noexcept:
        ResettableOption<T>(resetValue),
        UndoableOptionImpl<T>(initialValue),
        targetValue{ targetValue },
        stubbedCURLOPTvalue{ initialValue } {

    }

    template<typename T>
    OptionStub<T>::~OptionStub() {
        ResettableOption<T>::reset();
    }

    template<typename T>
    T OptionStub<T>::getTargetValue() const {
        return targetValue;
    }

    template<typename T>
    T OptionStub<T>::getActualValue() const {
        return stubbedCURLOPTvalue;
    }

	template<typename T>
    void OptionStub<T>::setTo(T targetValue) {
        stubbedCURLOPTvalue = targetValue;       
    }

}