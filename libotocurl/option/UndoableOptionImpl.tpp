#include <libotocurl/Exception.hpp>

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
        previous = getValue();
    }

}