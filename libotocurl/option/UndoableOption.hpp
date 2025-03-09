#ifndef LIBOTOCURL_OPTION_UNDOABLE_OPTION_HPP
#define LIBOTOCURL_OPTION_UNDOABLE_OPTION_HPP

#include <libotocurl/option/Option.hpp>

#include <optional>

namespace otocurl::option {

    /**
     * @brief Interface class for a CURLOPT which
     * can be undone.
     */
    class UndoableOption : virtual public Option {

        public:
            virtual ~UndoableOption() = default;
            void undo();

        private:
            virtual void doUndo() = 0;

    };

}

#endif