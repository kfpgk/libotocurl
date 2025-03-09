#ifndef LIBOTOCURL_OPTION_UNDOABLE_OPTION_IMPL_HPP
#define LIBOTOCURL_OPTION_UNDOABLE_OPTION_IMPL_HPP

#include <libotocurl/option/UndoableOption.hpp>

#include <optional>

namespace otocurl::option {

    /**
     * @brief CURLOPT that provides an interface
     * for undoing  the option.
     */
    template<typename T>
    class UndoableOptionImpl : public UndoableOption {

        public:
            UndoableOptionImpl() = default;
            virtual ~UndoableOptionImpl() = default;

        private:
            std::optional<T> previous;
            
            void doSet() final;
            void doUndo() final;

            [[nodiscard]] virtual T getValue() = 0;
            virtual void setTo(T value) = 0;

    };

}

#include <libotocurl/option/UndoableOptionImpl.tpp>

#endif