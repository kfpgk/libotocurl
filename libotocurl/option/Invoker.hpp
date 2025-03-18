#ifndef LIBOTOCURL_OPTION_INVOKER_HPP
#define LIBOTOCURL_OPTION_INVOKER_HPP

#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/UndoableOption.hpp>

#include <stack>
#include <memory>

namespace otocurl::option {

    /**
     * @brief Manages and keeps track of `Option` objects to
     * provide undo and redo functionality
     * 
     * @details
     * Patterns:
     *  - Invoker of the command pattern
     */
    class Invoker {

    public:
        /**
         * @brief Set the \p option and keep track to enable `undo()` and `redo()`
         */
        void set(std::shared_ptr<Option> option);

        /**
         * @brief Undo the most recent action which was invoked by the Invoker object
         */
        void undo();

        /**
         * @brief Redo the most recent action which has been undone by the Invoker object
         */
        void redo();

    private:
        /// @brief The stack that stores recently set objects that can be undone
        std::stack<std::shared_ptr<UndoableOption>> undoStack;

        /// @brief The stack that stores recently undon objects that can be redone
        std::stack<std::shared_ptr<UndoableOption>> redoStack;

    };

}

#endif