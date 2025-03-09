#include <libotocurl/Exception.hpp>

#include <iostream>

namespace otocurl::option {

    template<typename T>
    ResettableOption<T>::ResettableOption(const T& resetValue) :
        resetValue(resetValue) {

    }

    template<typename T>
    void ResettableOption<T>::reset() {
        if (resetValue) {
            setTo(resetValue.value());
        }
    }

}