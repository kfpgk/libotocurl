#include <libotocurl/option/UndoableOptionImpl.hpp>

#include <optional>

namespace otocurl::option {

    template<typename T>
    UndoableOptionImpl<T>::UndoableOptionImpl(T initialValue) : 
        current{ initialValue } {

    }

    template<typename T>
    void UndoableOptionImpl<T>::doUndo() {
        if (previous) {
            current = previous;
            setTo(current.value());
            previous.reset();
        }  
    }

    template<typename T>
    void UndoableOptionImpl<T>::doSet() {
        previous = current;
        current = getTargetValue();
        setTo(current.value());
    }

}