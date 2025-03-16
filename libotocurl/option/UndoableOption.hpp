#ifndef LIBOTOCURL_OPTION_UNDOABLE_OPTION_HPP
#define LIBOTOCURL_OPTION_UNDOABLE_OPTION_HPP

#include <libotocurl/option/Option.hpp>

#include <optional>

namespace otocurl::option {

    /**
     * @brief Interface class for a CURLOPT which can be undone.
     * 
     * The `Invoker` class makes use of this interface. It check if an object implements
     * this interface to identify undoable `Option` objects. Cannot use class template
     * `UndoableOptionImpl` for this.
     */
    class UndoableOption : virtual public Option {

    public:
        /**
         * @brief Virtual default destructor
         * 
         * Object may be deleted through derived pointer
         */
        virtual ~UndoableOption() = default;

        /**
         * @brief Undo the command to set an option
         */
        void undo();

    private:
        /**
         * @brief Pure virtual method to perform the actual undo operation
         */
        virtual void doUndo() = 0;

    };

}

#endif