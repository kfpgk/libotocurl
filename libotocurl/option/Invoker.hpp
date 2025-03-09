#ifndef LIBOTOCURL_OPTION_INVOKER_HPP
#define LIBOTOCURL_OPTION_INVOKER_HPP

#include <libotocurl/option/Option.hpp>
#include <libotocurl/option/UndoableOption.hpp>

#include <stack>
#include <memory>

namespace otocurl::option {

    /**
     * @brief Manages and keeps track of Option
     * objects
     * 
     * Patterns:
     *  - Invoker of the command pattern
     */
    class Invoker {

        public:
            void set(std::shared_ptr<Option> option);
            void undo();
            void redo();

        private:
            std::stack<std::shared_ptr<UndoableOption>> undoStack;
            std::stack<std::shared_ptr<UndoableOption>> redoStack;

    };

}

#endif