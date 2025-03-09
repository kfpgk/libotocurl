#include <libotocurl/option/UndoableOption.hpp>

namespace otocurl::option {

    void UndoableOption::undo() {
        doUndo();
    }

}