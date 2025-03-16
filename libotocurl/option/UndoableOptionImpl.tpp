#include <libotocurl/option/UndoableOptionImpl.hpp>

#include <optional>

namespace otocurl::option {

    template<typename T>
    void UndoableOptionImpl<T>::doUndo() {
        if (previous) {
            setTo(previous.value());
        }  
    }

    template<typename T>
    void UndoableOptionImpl<T>::doSet() {
        setTo(getValue());
        previous = getValue(); ///< TODO: This seems buggy
    }

}